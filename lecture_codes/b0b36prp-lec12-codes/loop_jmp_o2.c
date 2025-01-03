int main(void)
{   
   int ret = 0;   
   for (int i = 2147483640; i >= 0; ++i) {
      ret += i; 
   }
   return ret;
}
