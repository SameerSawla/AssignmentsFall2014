#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <iomanip>
#include <string>

std::vector<uintptr_t*> GLOBAL_addresses;
std::vector<std::string> GLOBAL_labels;
void compute_squares(uintptr_t a[],uintptr_t b[],uintptr_t &n)
{
	uintptr_t *traverse;
	uintptr_t *traverse2;
	for(traverse=a,traverse2=b;traverse<a+n;traverse++,traverse2++)
	{
		*traverse2 = *traverse * *traverse;
	}
	for(traverse=b;traverse<b+n;traverse++)
	{
		std::cout<<*traverse<<" ";
	}
	std::cout<<"\n";
}
void print_stack() { 

  assert (GLOBAL_addresses.size() == GLOBAL_labels.size());
  if (GLOBAL_addresses.size() == 0) {
    std::cerr <<  "No labeled addresses to print" << std::endl;
    return;
  }

  // Identify the range of stack data to print
  uintptr_t* min_address = GLOBAL_addresses[0];
  uintptr_t* max_address = GLOBAL_addresses[0];
  int max_label_width = GLOBAL_labels[0].size();
  for (int i = 1; i < GLOBAL_addresses.size(); i++) {
    if (GLOBAL_addresses[i] > max_address) { max_address = GLOBAL_addresses[i]; }
    if (GLOBAL_addresses[i] < min_address) { min_address = GLOBAL_addresses[i]; }
    if (GLOBAL_labels[i].size() > max_label_width) { max_label_width = GLOBAL_labels[i].size(); }
  }

  // double check that my uintptr_t is actually the size of a pointer
  assert (sizeof(uintptr_t) == sizeof(void*));
  // double check that the start and end address are aligned 
  assert ((((uintptr_t)min_address) & (sizeof(uintptr_t)-1)) == 0);
  assert ((((uintptr_t)max_address) & (sizeof(uintptr_t)-1)) == 0);

  // double check that the range of address is reasonable 
  if (max_address-min_address > 1000) {
    std::cerr << "WARNING: trying to print too much" << std::endl;
    return;
  }

  // loop over all addresses in the range (plus some above & below)
  std::cout << "-----------------------------------------" << std::endl;
  for (uintptr_t* address = max_address+5; address >= min_address-5; address--) {
    std::string label = "";
    for (int i = 0; i < GLOBAL_addresses.size(); i++) {
      if (address == GLOBAL_addresses[i]) { label = GLOBAL_labels[i]; }
    }
    std::cout << std::setw(max_label_width) << label << " location: " << address;

    // this location might store a value (we assume all values are integers)
    int an_int = (int)(*address);
    // or it might store an address (so we cast it to a pointer)
    uintptr_t* an_address = (uintptr_t*)(*address);

    // if it's a value
    if (an_int > -1000 && an_int < 1000) {
      std::cout << "  VALUE:   " << an_int << std::endl;
    } 
    // if it's an address
    else if (an_address >= min_address-1000 && an_address <= max_address+1000) {
      std::cout << "  POINTER: " << an_address << std::endl;
    }
    // otherwise it's probably garbage
    else { 
      std::cout << "  garbage? " << std::endl;
    }
  }
  std::cout << "-----------------------------------------" << std::endl;
}
// add a label to a particular address in the stack
// NOTE: We use global variables for simplicity for this exercise
void label_stack(uintptr_t* address, const std::string& tag) {
  for (int i = 0; i < GLOBAL_addresses.size(); i++) {
    // check to see if that address is already labeled
    if (address == GLOBAL_addresses[i]) {
      // add additional labels
      GLOBAL_labels[i] += ", " + tag;      
      return;
    }
  }
  GLOBAL_addresses.push_back(address);
  GLOBAL_labels.push_back(tag);
}


// clear all previous labels
// NOTE: We use global variables for simplicity for this exercise
void clear_stack_labels() {
  GLOBAL_addresses.clear();
  GLOBAL_labels.clear();
}


int main()
{
	uintptr_t a[5] = {1,2,3,4,5};
	uintptr_t b[5];
	uintptr_t n=5;
	// std::cout<<"Before compute_squares\n";
	// std::cout<<"contents of a \n";
	// for(unsigned int i=0;i<n;i++)
	// {
	// 	std::cout<<a[i]<<" ";
	// }

	// std::cout<<"\ncontents of b \n";
	// for(unsigned int i=0;i<n;i++)
	// {
	// 	std::cout<<b[i]<<" ";
	// }
	// std::cout<<"\n";
	label_stack(&a[4],"a[4]");
	label_stack(&a[3],"a[3]");
	label_stack(&a[2],"a[2]");
	label_stack(&a[1],"a[1]");
	label_stack(&a[0],"a[0]");

	label_stack(&b[4],"b[4]");
	label_stack(&b[3],"b[3]");
	label_stack(&b[2],"b[2]");
	label_stack(&b[1],"b[1]");
	label_stack(&b[0],"b[0]");

	print_stack();
	compute_squares(a,b,n);
	print_stack();

	clear_stack_labels();

	// std::cout<<"\n\nAfter compute_squares\n";
	// std::cout<<"changed contents of a \n";
	// for(unsigned int i=0;i<n;i++)
	// {
	// 	std::cout<<a[i]<<" ";
	// }

	// std::cout<<"\nchanged contents of b \n";
	// for(unsigned int i=0;i<n;i++)
	// {
	// 	std::cout<<b[i]<<" ";
	// }
	// std::cout<<"\n";

}