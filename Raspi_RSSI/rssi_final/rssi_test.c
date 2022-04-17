#include <iostream>


int main(){

FILE *fp,*outputfile;
char var[40];

fp = popen("echo -e connect FC:D4:36:09:88:92\nquit | bluetoothctl scan on", "r");

while(fgets(var, sizeof(var), fp) != NULL) {
     printf("%s", var);
}
pclose(fp);

outputfile = fopen("text.txt", "a");
fprintf(outputfile,"%s\n",var);
fclose(outputfile);

return 0;
}
