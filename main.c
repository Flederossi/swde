#include <windows.h>
#include <stdio.h>
#include <dirent.h>

// Max -> 10
#define FPS 10

void startBackgroundProcess(int vis){
	HWND window;
	window = FindWindow("ConsoleWindowClass", NULL);
	ShowWindow(window, vis);
}

const wchar_t *convertChar(const char *c){
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc;
	mbstowcs(wc, c, cSize);

	return wc;
}

int main(){
	wchar_t path[512] = L"C:\\swde\\";
	DIR *d;
	struct dirent *dir;

	startBackgroundProcess(0);

	if (d){
		while (1){
			d = opendir("C:\\swde");

			while ((dir = readdir(d)) != NULL){
				if (dir->d_type != DT_DIR){
					printf("Load %s\n", dir->d_name);
					
					const wchar_t *wfile = convertChar(dir->d_name);
					wcscat(path, wfile);

					SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void * ) path, SPIF_UPDATEINIFILE);

					usleep(1000000/FPS);
					wcscpy(path, L"C:\\swde\\");
				}
			}

			closedir(d);
		}
	}else{
		printf("Couldn't find directory 'C:/swde' please create it...");
	}
	return 0;
}
