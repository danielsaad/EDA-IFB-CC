
int* f(int** v){
	int* ptr = malloc(sizeof(int) * 100000);
	*v = ptr;
}

int main(void){
	int* v;
	f(&v);
}