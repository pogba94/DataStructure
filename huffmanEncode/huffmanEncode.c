#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "windows.h"

#define MAX_HUFFMAN_LEAF_NODE    (300)
#define	MAX_WEIGHT               (1000)


typedef float ElemType_t;

/* Huffman node structrue */
typedef struct HTNode
{
	ElemType_t weight;
	int parent;
	int lchild;
	int rchild;
	char ch;
}HTNode,*HuffmanTree;

/* Huffman encode structure */
typedef struct HuffmanCode
{
	char *HCode;
	int size;
	ElemType_t weight;
	char ch;
}HuffmanCode;

const char file_path[] = "D:/test.pdf";
//const char file_path[] = "D:/server.py";

HuffmanTree createHuffmanTree(ElemType_t *weightArr,char *map,int n)
{
	HuffmanTree HT;
	int i,j,x1,x2;
	ElemType_t min1,min2;
	if(weightArr == NULL || n <= 0 || n > MAX_HUFFMAN_LEAF_NODE)
		return NULL;
	HT = (HuffmanTree)malloc(sizeof(HTNode)*(2*n-1));
	if(HT == NULL)
		return NULL;
	/* Initialize node */
	for(i=0;i<2*n-1;i++){
		HT[i].weight = 0;
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
	}
	for(i=0;i<n;i++){
		HT[i].weight = weightArr[i];
	}
	if(map != NULL){
		for(i=0;i<n;i++)
			HT[i].ch = map[i];
	}
	/* consturct huffman tree */
	for(i=0;i<n-1;i++){
		min1 = min2 = MAX_WEIGHT;
		x1 = x2 = 0;
		for(j=0;j<n+i;j++){
			if(HT[j].weight < min1 && HT[j].parent == -1){
				x2 = x1;
				min2 = min1;
				x1 = j;
				min1 = HT[j].weight;
			}else if(HT[j].weight < min2 && HT[j].parent == -1){
				min2 = HT[j].weight;
				x2 = j;
			}
		}
		HT[n+i].weight = min1 + min2;
		HT[n+i].lchild = x1;
		HT[n+i].rchild = x2;
		HT[x1].parent = n+i;
		HT[x2].parent = n+i;
		#if 0
		printf("x1=%d,x2=%d,min1.weight=%d,min2.weight=%d\n",x1,x2,HT[x1].weight,HT[x2].weight); //for debug
		#endif
	}
	return HT;
}

static void printHTNode(HuffmanTree HT)
{
	int p =0;
	if(HT != NULL){
		while(HT[p].lchild == -1 && HT[p].rchild == -1){
			p++;
		}
		p = 2*p-1;
		for(int i=0;i<p;i++){
			printf("---index:%d---weight:%f---lchild:%d---rchild:%d---parent:%d\n---char:%d",i,HT[i].weight,HT[i].lchild,HT[i].rchild,HT[i].parent,HT[i].ch);
		}
	}
}

static void printHTLeafNode(HuffmanTree HT)
{
	int p = 0;
	if(HT != NULL){
		while(HT[p].lchild == -1 && HT[p].rchild == -1){
			p++;
		}
		for(int i=0;i<p;i++){
			printf("---index:%d---weight:%f---parent:%d\n---char:%d",i,HT[i].weight,HT[i].parent,HT[i].ch);
		}
		printf("\n");
	}
}

static void printHuffmanCode(HuffmanCode *HC,int size)
{
	if(HC == NULL || size <= 0)
		return;
	for(int i=0;i<size;i++){
		printf("---index:%d---HCode:%s---weight:%f----char:%d\n",i,HC[i].HCode,HC[i].weight,HC[i].ch);
	}
}

HuffmanCode* huffmanCodeEncode(HuffmanTree HT)
{
	int leafNum = 0;
	int p;
	HuffmanCode *HC;
	char *buffer;
	if(HT == NULL)
		return NULL;
	while(HT[leafNum].lchild == -1 && HT[leafNum].rchild == -1){
		leafNum++;
	}
	HC = (HuffmanCode*)malloc(sizeof(HuffmanCode)*(leafNum));
	if(HC == NULL)
		return NULL;
	buffer = (char*)malloc(leafNum);
	if(buffer == NULL)
		return NULL;
	for(int i=0;i<leafNum;i++){
		int tmp;
		HC[i].weight = HT[i].weight;
		HC[i].size = 0;
		HC[i].ch = HT[i].ch;
		tmp = i;
		p = HT[i].parent;
		while(p != -1){
			if(HT[p].lchild == tmp){
				buffer[HC[i].size++] = '0';
			}else{
				buffer[HC[i].size++] = '1';
			}
			tmp = p;   //take care!
			p = HT[p].parent;
		}
		HC[i].HCode = (char*)malloc(HC[i].size+1);
		if(HC[i].HCode == NULL)
			return NULL;
		for(int j=0;j<HC[i].size;j++)
			HC[i].HCode[j] = buffer[HC[i].size-1-j];
		HC[i].HCode[HC[i].size] = '\0';
		memset(buffer,0x0,strlen(buffer));
		#if 0
		printf("node %d's huffman code:%s,size=%d\n",i,HC[i].HCode,HC[i].size);
		#endif
	}
	return HC;
}


void huffmanTreeTest(void)
{
	int num;
	ElemType_t *weightArray;
	HuffmanTree myHuffmanTree;
	HuffmanCode *myHuffmanCode;
	printf("please input the num of huffman tree leaf:");
	scanf("%d",&num);
	weightArray = (ElemType_t*)malloc(sizeof(ElemType_t)*num);
	if(weightArray == NULL)
		return;
	for(int i=0;i<num;i++){
		printf("please input the weight of number%d :",i);
		scanf("%f",&weightArray[i]);
	}
	printf("HuffmanTree consturcting...\n");
	myHuffmanTree = createHuffmanTree(weightArray,NULL,num);
	if(myHuffmanTree == NULL){
		printf("huffman tree consturct failed\n");
		return;
	}
	printf("\n-----------traverse all leaf nodes of huffman tree----------\n\n");
//	printHTLeafNode(myHuffmanTree);
	printHTNode(myHuffmanTree);
	myHuffmanCode = huffmanCodeEncode(myHuffmanTree);
	if(myHuffmanCode == NULL)
		printf("get huffman code failed\n");
	printf("\n----------------print huffman code----------------\n\n");
	printHuffmanCode(myHuffmanCode,num);
}


static int getHuffmanInfo(const char *filePath,ElemType_t ** weight,char **map,int *n)
{
	FILE *fp;
	int size,p,leafNum;
	unsigned int *countArr;
	ElemType_t *weightArr;
	char *mapArr;
	fp = fopen(filePath,"rb");
	if(fp == NULL){
		printf("cannot open file\n");
		return -1;
	}
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	printf("file size:%d\n",size);
	countArr = (unsigned int*)malloc(sizeof(unsigned int)*256);
	if(countArr == NULL)
		return -2;
	memset(countArr,0x0,sizeof(unsigned int)*256);
	fseek(fp,0,SEEK_SET);
	for(int i=0;i<size;i++){
		countArr[fgetc(fp)]++;
	}
	leafNum = 0;
	for(int i=0;i<256;i++){
		if(countArr[i] != 0)
			leafNum++;
	}
//	printf("leaf num:%d\n",leafNum);
	weightArr = (ElemType_t *)malloc(sizeof(ElemType_t)*leafNum);
	if(weightArr == NULL){
		free(countArr);
		return -2;
	}
	mapArr = (char*)malloc(leafNum);
	if(mapArr == NULL){
		free(countArr);
		return -2;
	}
	p = 0;
	for(int i=0;i<256;i++){
		 if(countArr[i] != 0){
		 	weightArr[p] = (ElemType_t)countArr[i]/(ElemType_t)size;
		 	mapArr[p] = i;
		 	p++;
		 }
	}
	*weight = weightArr;
	*n = leafNum;
	*map = mapArr;
	printf("\nprint weight array:\n\n");
	for(int i=0;i<leafNum;i++){
		printf("----index:%d----char:%d----weight:%f----\n",i,mapArr[i],weightArr[i]);
	}
	free(countArr);
	fclose(fp);
	return 0;
}

int huffmanConpreess(const char *srcFile,const char *dstFile)
{
	FILE *pSrc,*pDst;
	HuffmanCode *HC;
	HuffmanTree HT;
	ElemType_t *weight;
	char *map;
	char buf = 0;
	char c;
	int i,j,n,srcFileSize;
	int pBit = 0,index;
	int start,end;

	if(srcFile == NULL || dstFile == NULL)
		return -1;
	pSrc = fopen(srcFile,"rb");
	pDst = fopen(dstFile,"wb");
	if(pSrc == NULL || pDst == NULL)
		return -2;
	fseek(pSrc,0,SEEK_END);
	srcFileSize = ftell(pSrc);
	printf("src file size:%d\n",srcFileSize);
	if(getHuffmanInfo(srcFile,&weight,&map,&n))
		return -3;
	HT = createHuffmanTree(weight,map,n);
	if(HT == NULL)
		return -4;
	HC = huffmanCodeEncode(HT);
	if(HC == NULL)
		return -5;
	/* write huffman code to file head*/
	fwrite(&n,sizeof(int),1,pDst);
	for(i=0;i<n;i++)
		fwrite(&(HC[i].ch),sizeof(char),1,pDst);
	for(i=0;i<n;i++)
		fwrite(&(HC[i].weight),sizeof(ElemType_t),1,pDst);
	/* start to encode */
	rewind(pSrc);
	start = GetTickCount();
	for(i=0;i<srcFileSize;i++){
		c = fgetc(pSrc);
		for(j=0;j<n;j++){
			if(HC[j].ch == c){
				index = j;
				break;
			}
		}
		for(j=0;j<HC[index].size;j++){
			if(pBit == 8){//buffer is full,start to write to file 
				fwrite(&buf,sizeof(char),1,pDst);
				buf = 0;
				pBit = 0;
			}
			buf |= ((HC[index].HCode[j]-'0')<<(7-pBit));
			pBit++; 
		}
	}
	end = GetTickCount();
	printf("time cost:%d ms\n",end-start);
	if(pBit != 8){
		fwrite(&buf,sizeof(char),1,pDst);
	}
	fclose(pSrc);
	fclose(pDst);
	return 0;
}

int huffmanDeconpress(const char *srcFile,const char *dstFile)
{
	HuffmanTree HT;
	ElemType_t *weightArr;
	char *map;
	char buf;
	int leafNum,srcFileSize;
	int pBit = 0;
	int curHTNode;

	if(srcFile == NULL || dstFile == NULL)
		return -1;
	FILE *pSrc,*pDst;
	pSrc = fopen(srcFile,"rb");
	if(pSrc == NULL)
		return -2;
	pDst = fopen(dstFile,"wb");
	if(pDst == NULL)
		return -2;
	fseek(pSrc,0,SEEK_END);
	srcFileSize = ftell(pSrc);
//	printf("src file size:%d\n",srcFileSize);
	rewind(pSrc);
	fread(&leafNum,sizeof(int),1,pSrc);
//	printf("leaf num:%d\n",leafNum);
	weightArr = (ElemType_t*)malloc(sizeof(ElemType_t)*leafNum);
	if(weightArr == NULL)
		return -3;
	map = (char*)malloc(leafNum);
	if(map == NULL){
		free(weightArr);
		return -3;
	}
	fread(map,sizeof(char),leafNum,pSrc);
	#if 0
	printf("\nprint map:\n");
	for(int i=0;i<leafNum;i++){
		if(i%10==0)
			printf("\n");
		printf("%d\t",map[i]);
	}
	#endif
	fread(weightArr,sizeof(ElemType_t),leafNum,pSrc);
	#if 0
	printf("\nprint weight\n\n");
	for(int i=0;i<leafNum;i++){
		if(i%10==0)
			printf("\n");
		printf("%f\t",weightArr[i]);
	}
	#endif
	HT = createHuffmanTree(weightArr,map,leafNum);
	if(HT == NULL){
		free(weightArr);
		free(map);
		return -4;
	}
//	printHTLeafNode(HT);

	/* start to decode */
	curHTNode = 2 * leafNum -2;
	while(ftell(pSrc) != srcFileSize){
		buf = fgetc(pSrc);
		pBit = 8;
		while(pBit){
			if(HT[curHTNode].lchild == -1 && HT[curHTNode].rchild == -1){
				fwrite(&HT[curHTNode].ch,sizeof(char),1,pDst);
				curHTNode = 2 * leafNum -2;
			}
			if((buf >> (pBit-1)) & 0x1){
				curHTNode = HT[curHTNode].rchild;
			}else{
				curHTNode = HT[curHTNode].lchild;
			}
			pBit--;
		}
	}
	free(HT);
	fclose(pSrc);
	fclose(pDst);
	return 0;
}

void conpressFileTest(const char *filePath)
{
	int start,end,p1,p2;
	char postFix[] = ".huffman";
	char conpressFileName[] = "conpress";
	char deconpressFileName[] = "deconpress"; 
	char *conpressFilePath,*deconpressFilePath;

	p1 = 0;
	while(filePath[++p1] != '.');
	while(filePath[--p1] != '/');
	p1++;
    conpressFilePath = (char*)malloc(strlen(filePath)+20);
    if(conpressFilePath == NULL)
    	return;
    deconpressFilePath = (char*)malloc(strlen(filePath)+20);
    if(deconpressFilePath == NULL){
    	free(conpressFilePath);
    	return;
    }
    memset(conpressFilePath,0x0,sizeof(conpressFilePath));
    memset(deconpressFilePath,0x0,sizeof(deconpressFilePath));

    strncpy(conpressFilePath,filePath,p1);
    strcpy(conpressFilePath+p1,conpressFileName);
    strcpy(conpressFilePath+p1+strlen(conpressFileName),postFix);

    p2 = 0;
    while(filePath[++p2] != '.');

    strncpy(deconpressFilePath,filePath,p1);
    strcpy(deconpressFilePath+p1,deconpressFileName);
    strcpy(deconpressFilePath+p1+strlen(deconpressFileName),filePath+p2);

	start = GetTickCount();
	huffmanConpreess(filePath,conpressFilePath);
	end = GetTickCount();
	printf("conpress time cost:%d ms\n",end-start);
	start = GetTickCount();
	huffmanDeconpress(conpressFilePath,deconpressFilePath);
	end = GetTickCount();
	printf("deconpress time cost:%d ms\n",end-start);
}

int main(void)
{
	conpressFileTest(file_path);
//	huffmanTreeTest();
	for(;;);
}

