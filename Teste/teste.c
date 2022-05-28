
// #include <stdio.h>
// #include <unistd.h>

// int main(int argc, char const *argv[])
// {
// 	/* code */
// 	printf("\n\n[#");
// 	// sleep(10);
// 	fflush(stdout);
// 	printf("[##\n");

// 	return 0;
// }

#include <stdio.h>
#include <unistd.h>

void loading_bar(int time);

   int main (){
    //    int i = 0;
    //    for (i = 0; i < 100; i++){
    //        printf("\rIn progress %d", i + 1);
	// 	   fflush(stdout);
	// 	   usleep(50000);
    //    }
    //    printf("\n");

		printf("Teste de barra de carregamento\n");
		loading_bar(500);
   }

   	void loading_bar(int time) {
		int charSize = 100;
		char loading[charSize + 20];
		int loaded = 0;

		for(int i = 0; i < charSize; i++) {
			if(i == 0) {
				loading[i] = '[';
			} else if(i == charSize-1) {
				loading[i] = ']';
			} else {
				loading[i] = ' ';
			}
		}

		for(int i = 0; i < charSize; i++) {
			if(i == 0) {
				loading[i] = '[';
			} else if(i == charSize-1) {
				loading[i] = ']';
			} else {
				loading[i] = '#';
			}

			// for(int j = 0; j < 100; j++) {
				printf("\r%s", loading);
				fflush(stdout);
				usleep(time * 100);
			// }
		}
		printf("\n");

	}	