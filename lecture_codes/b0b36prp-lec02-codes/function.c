
void function(void); //hlavička funkce

int main(void)
{
   return 0;
}

void function(void)  //definice funkce
{
   int variable; // local function variable

   void inner_function() // definition of inner function 
   {                     // is not allowed in C
   }
   function(); // we can call function from the function
}
