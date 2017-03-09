#include "array.h"

struct element{
	int data;
	struct element* next;
}element;

Array::Array(){
	head = nullptr;
	tail = nullptr;
	blockSize = 0;
	N = 0;
	offset = 0;
}

Array::Array(int blockSize, int numberOfBlocks, int offset){
	this->blockSize = blockSize;
	this->N = numberOfBlocks;
	this->offset = offset;
	head = nullptr;
	tail =nullptr;

	for(int i = 0; i < blockSize; i++){
		if(!head){
			head = new struct element;
			head->data = i;
			head->next = head;
			tail = head;
		}else{
			tail->next = new struct element;
			(tail->next)->next = head;
			(tail->next)->data = i;
			tail = tail->next;
		}
	}
}

void Array::fillWithZigzagIndex(){
	/*for(int i = 0; i < numberOfBlocks; i++){
		for(int j = 0; j < this->blockSize; j++){
			if(i == numberOfBlocks - 1){
				if(j == blockSize/numberOfBlocks - 1){
					*(*(elements + i) + j) = 0;
				}else{
					*(*(elements + i) + j) = i - offset * (numberOfBlocks) + j + 1;
				} 
			}else{
				*(*(elements + i) + j) = i + blockSize/numberOfBlocks + j;
			}
		}
	}*/
}

std::ostream& operator << (std::ostream& output, const Array& array){
	/*output << "Block size " << array.blockSize << ", ";
	output << "Number of block " << array.numberOfBlocks << ", ";
	output << "Offset " << array.offset << std::endl;
	for(int i = 0; i < array.numberOfBlocks; i++){
		for(int j = 0; j < array.blockSize; j++){
			output << (int)*(*(array.elements + i) + j) << " ";
		}
		output << std::endl;
	}
	return output;*/
}

/*unsigned char Array::operator [] (int index){
	int blockNumber;
	for(int i = 0; i < numberOfBlocks; i++){
		if((index >= blocks[i].startIndex) && (index <= blocks[i].endIndex)){
			blockNumber = i;
		}
	}

	return elements[blockNumber * offset + index - blocks[blockNumber].startIndex];
}*/