#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

unsigned int rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

int reverse(int input){
  int reverse = 0;
  
  while(input){
    reverse *= 10;
    reverse += input % 10;
    input /= 10 ;
    
  }
    return reverse;
}

int recursiveReverse(int input,int output){
  if(input<10)
    return output*10 + input;
  else{
    output *=10;
    output += (input % 10);
    return recursiveReverse(input/10,output);
  }

}

  
int main(){

  int input;
  int output=0;
  int output2=0;
  int i;

  
  for (i=0;i<1000;i++){
    input = rand_interval(0,1000000);
    output = reverse(input);
    output2 = recursiveReverse(input,0);
  
    printf("Input=%d,\toutput=%d\toutput2=%d\n",input,output,output2);

    if(input % 10){
      assert( input == reverse(output));
      assert( input == recursiveReverse(output2,0));
    }
  }
}
