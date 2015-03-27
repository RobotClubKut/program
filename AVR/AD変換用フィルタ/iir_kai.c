

int IIR(int n,char p){
	/*
	static int z[4][n]={0};
	nはフィルタをかける個数
	int add[3][n] = {0};
	のnも同様
	*/
	static int z[4][14]={0};//処理の後に代入させる
	//int a0=0x7b; //4.12 fc = fs / 16
	int a0 = 0x24; //fc = fs /32
	int	a1=a0 * 2,a2=a0;
	//int b1=0x174,b2=0x93;//8.8 fc = fs /16
	int b1=0x1b8,b2=0xc1;//fc = fs / 32
	int add[3][14] = {0};

	a0 = a0 << 12;
	a1 = a1 << 12;
	a2 = a2 << 12;
	
	b1 = b1 << 12;
	b2 = b2 << 12;
	
	n = n << 6;
	
	a2 = (z[1][p] << 8) * a2;
	a1 = (z[0][p] << 8) * a1;
	a0 = n << 6 * a0;
	
	b2 = (z[3][p] << 8) * b2;
	b1 = (z[2][p] << 8) * b1;
	
	z[1][p] = z[0][p];
	z[0][p] = n >> 2;
	z[3][p] = z[2][p];
	z[2][p] = add[0][p];
	
	add[0][p] = add[1][p] + (a0 >> 4);
	add[0][p] = add[0][p] >> 8;
	add[1][p] = (a1 >> 4) + b1 + add[2][p];
	add[2][p] = (a2 >> 4) - b2;
	
	return add[0][p];
}