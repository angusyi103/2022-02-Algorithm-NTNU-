#include <stdio.h>
#include <string.h>

int main()
{
    
    int temp = 0;  //state
    int count = 0; //shrimp num
    int len = 0;  //string length
    int i;
    char x[1001];
    char y[1001];
    
    scanf("%s", x);
    scanf("%s", y);
    
    len = strlen(y);

    if (len == 1) {
        printf("%d", count);
        return 0;
    }


    for(i = 0; i < len; i++){
        if(temp == 0){
            if(x[i] == '0' && y[i] == '0'){
                temp = 2;
            }
            else if((x[i] == '0' && y[i] == '1') || (x[i] == '1' && y[i] == '0')){
                temp = 1;
            }
        }
        else if(temp == 1){
            if(x[i] == '0' && y[i] == '0'){
                count++;
                temp = 0;
            }
            else if((x[i] == '0' && y[i] == '1') || (x[i] == '1' && y[i] == '0')){
                temp = 1;
            }
            else{
                temp = 0;
            }
        }
        else if(temp == 2){
            if(x[i] == '0' && y[i] == '0'){
                count++;
                temp = 3;
            }
            else if((x[i] == '0' && y[i] == '1') || (x[i] == '1' && y[i] == '0')){
                count++;
                temp = 0;
            }
            else{
                temp = 0;
            }
        }
        else{
            if(x[i] == '0' && y[i] == '0'){
                count++;
                temp = 0;
            }
            else if((x[i] == '0' && y[i] == '1') || (x[i] == '1' && y[i] == '0')){
                temp = 1;
            }
            else{
                temp = 0;
            }
        }
    }

    printf("%d", count);
    return 0;
}
