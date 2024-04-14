#include <stdio.h>
#include "elfread.h"

int main(int argc, char** argv) {
	if (argc != 2)
		return 1;
	FILE* fp = fopen(argv[1], "r");

	if (fp == NULL) {
		printf("Can not open file! \n");
		return 1;
	}


	//读取ELF Header
	ElfN_Ehdr elf_header;
	read_elf_header(fp, &elf_header);
	print_elf_header(elf_header);

	//读取Section Header Table
	fseek(fp, elf_header.e_shoff, SEEK_SET);
	ElfN_Shdr section_headers[elf_header.e_shnum];
	for (int i = 0; i < elf_header.e_shnum; i++) {
        	read_section_header(fp, &section_headers[i], &elf_header, i);
   	}
	print_section_headers(fp, &elf_header, section_headers, elf_header.e_shnum);


	//找到符号表和字符串表
	ElfN_Shdr* symtab_hdr = NULL;
	ElfN_Shdr* strtab_hdr = NULL;
	for(int i = 0; i < elf_header.e_shnum; i++){
		if(section_headers[i].sh_type == SHT_SYMTAB){
			symtab_hdr = &section_headers[i];
			strtab_hdr = &section_headers[symtab_hdr->sh_link];
			break;
		}

	}

	//读取Symbol Table
	int syms_num = symtab_hdr->sh_size / symtab_hdr->sh_entsize;
	ElfN_Sym symtab[syms_num];
	read_symtab(fp, symtab, symtab_hdr);
	print_symtab(fp, symtab, strtab_hdr, syms_num);

	fclose(fp);
	return 0;
}
