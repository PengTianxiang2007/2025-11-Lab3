#include <stdio.h>
#include <string.h>

typedef struct {
    char name[1000];
    int score;
    int hour;
    int minute;
    int time;
}Record;

int main(){
    int n;
    scanf("%d",&n);

    Record records[1009];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d:%d", records[i].name, &records[i].score, &records[i].hour, &records[i].minute);
        records[i].time = records[i].hour*60 + records[i].minute;
    }

    for (int i = 0 ; i < n - 1 ; i++){
        Record temp;
        for (int j = 0 ; j < n - 1 - i ; j++){
            if (records[j].score < records[j+1].score){
                temp = records[j];
                records[j] = records[j+1];
                records [j+1] = temp;
            }
            
        }
    }

    for (int i = 0 ; i < n - 1 ; i++ ){
        Record temp;
        for (int j = 0 ; j < n - 1 - i ; j++){
            if (records[j].score == records[j+1].score && records[j].time > records[j+1].time){
                temp = records[j];
                records[j] = records[j+1];
                records [j+1] = temp;
            }       
        }
    }

    for (int i = 0 ; i < n - 1 ; i++){
        Record temp;
        for (int j = 0 ; j < n - 1 - i ; j++){
            if (records[j].score == records[j+1].score && records[j].time == records[j+1].time && 
            strcmp(records[j].name , records[j+1].name)>0){
                temp = records[j];
                records[j] = records[j+1];
                records [j+1] = temp;
            }
        }
    }
 
    for (int i = 0 ; i < n ; i++ ){
        printf("%s\n",records[i].name);
    }

    
    return 0;
}