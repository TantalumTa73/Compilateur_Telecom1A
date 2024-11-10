int main() {
   int i = -1;
   while(i < 6){
      i++;
      if (i == 1){
         continue;
      }
      if (i == 4){
         break;
      }
      print_int(i);
   }  
   return 0;
}