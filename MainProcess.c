#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(){
char str [400];
char str1[200], str2[100], str3[100];
int i, j;

printf("please enter the encrypted text:\n");
fgets(str, 400, stdin);

for(i=0 ; i < 400 ; i++){
if(str[i]=='#'){
    strncpy(str1, &str[0],i);
    str1[i] = '\0';
    printf("The original string is: %s",str);
    printf("str1 is: %s\n", str1);
    break;
}
}
i+=3;
for(j = i ; j < 400 ; j++){
if(str[j]=='#'){
    strncpy(str2, &str[i],j);
    str2[j-i] = '\0';
    printf("str2 is: %s\n", str2);
    break;
}
}
j+=3;
strncpy(str3, &str[j], 400);
str3[400-j] = '\0';
printf("str3 is: %s", str3);



return 0;
}

