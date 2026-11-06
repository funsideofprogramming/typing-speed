#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdbool.h>

char *txt = "The quick brown fox jumps over the lazy dog";
typedef unsigned long int timestamp;
// return the current timestamp in microsec 
timestamp get_micros(){
    struct timeval tv;
    int res = gettimeofday(&tv, NULL);
    if(res != 0){
        perror("Getting time failed\n");
        return -1;
    }
    unsigned long int timestamp = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
    return timestamp;

}

int get_word_count(char *s){
    int counter = 0;
    bool inside_word = false;
    for(int i = 0; i < strlen(s); ++i){
        if(s[i]== ' ' && inside_word == true){
            //just entered a new word
            inside_word = false;
        }else if(s[i] != ' ' && inside_word == false){
            //just entered a new word
             counter++;
            inside_word = true;
        }
    }
    return counter;
}

float calc_accuracy(char *reference, char *provided){
    int correct = 0;
    for(int i = 0; i < strlen(reference); ++i){
        if(reference[i] == provided[i]){
            correct++;
        }
    }
    return ((float) correct) / (float) strlen(reference);
}
int main(int argc, char *argv[]){
    
    printf("Type \"%s\"\n", txt);
    
    char typed_buffer[100];

    timestamp start_micros = get_micros();
    fgets(typed_buffer,sizeof(typed_buffer), stdin); 
    
    int len = strlen(typed_buffer);
    typed_buffer[len-1] = '\0';
    timestamp end_micros = get_micros();
    
    timestamp micros = end_micros - start_micros;
    int wc = get_word_count(typed_buffer);
    double typing_speed = (double) wc / ((double)micros/1000/1000/60);
    
    float accuracy_percent = calc_accuracy(txt, typed_buffer) * 100;
    printf("User typed \"%s\"\n", typed_buffer);
    printf("Typing speed: %.2f words/min \n", typing_speed);
    printf("Accuracy = %.2f%%\n", accuracy_percent);
    return 0;
}
