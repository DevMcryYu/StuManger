/*一个学生成绩管理的程序。由键盘输入数据（考虑输入数据输入的格式及输入数据的有效性）
，然后进行以下的功能实现。程序要求主函数是一个功能选择菜单，其它各功能都用各自的函数
实现；数据信息用文件保存。*/
/*Ver2.0更新内容
1.新增登陆系统
2.新增输入验证
3.支持保存文本格式数据
4.排序优化
5.修复一些Bug
6.界面优化
*/
/*头文件*/
#include "Head.h"
typedef struct Student Data;

/*定义结构体*/
Data stu[100];
int num = 0;
int Log = 0;

void stu_Input();
void Login();
void clear();
int Available();
void Save_stu();
void Insert_stu();
void Delete_stu();
void Modify_stu();
void Select_stu();
void Mark_grade();
void ReorderByID();
void Display_stu();
void Reorder_stu();
void IO_ReadInfo();
void IO_WriteInfo();
void Average_Subject();
void Display_Single(int i);
int Check_Format(float Mark);
int Search_byIndex(char id[]);
int Search_byName(char name[]);
int ID_Different(char id[], int num);
float Avg(Data stu);
/*主函数*/
void main()
{
	char choice;
	IO_ReadInfo();
	Login();
	system("cls");
	while (Log!=0)
	{
		/*主菜单*/
		printf("\t\t\t--------学生成绩管理系统--------\n");
		printf("\t\t\t        1.新增学生成绩\n");
		printf("\t\t\t        2.删除学生成绩\n");
		printf("\t\t\t        3.更改学生成绩\n");
		printf("\t\t\t        4.查询学生成绩\n");
		printf("\t\t\t        5.打印学生成绩\n");
		printf("\t\t\t        6.各科平均成绩\n");
		printf("\t\t\t        7.学生成绩排名\n");
		printf("\t\t\t        8.各分数段人数\n");
		printf("\t\t\t        9.退出管理系统\n");
		printf("\t\t\t--------------------------------\n");
		printf("\t\t\t\t请输入序号继续:");
		scanf("%s", &choice);
		clear();
		switch (choice)
		{
		case '1': if (Available() == -1) break; Insert_stu(); system("cls"); break;
		case '2': if (Available() == -1) break; Delete_stu(); system("cls"); break;
		case '3': if (Available() == -1) break; Modify_stu(); system("cls"); break;
		case '4': Select_stu(); system("cls"); break;
		case '5': Reorder_stu(); ReorderByID(); Display_stu(); system("cls"); break;
		case '6': Average_Subject(); system("cls"); break;
		case '7': Reorder_stu(); Display_stu(); system("cls"); break;
		case '8': Mark_grade(); system("cls"); break;
		case '9': Reorder_stu(); ReorderByID(); Save_stu(); exit(0); break;
		default: {
					printf("\t\t\t\t\t输入无效，请重新选择:\n");
					continue;
				 }
		}
		IO_WriteInfo();
	}
}
/*求成绩平均值*/
float Avg(Data stu)
{
	return (stu.Mark1 + stu.Mark2 + stu.Mark3 + stu.Mark4) / 4;
}
/*清除缓冲区*/
void clear()
{
	while (getchar() != '\n')
		continue;
}
/*将学生信息从文件读出*/
void IO_ReadInfo()
{
	FILE *fp;
	int i;
	if ((fp = fopen("Database.txt", "r")) == NULL)
	{
		printf("\t\t\t\t文件打开失败.\n");
		return;
	}
	if ((fread(&num, sizeof(int), 1, fp)) != 1)
	{
		num = 0;
	}
	else
	{
		for (i = 0; i < num; i++)
		{
			fread(&stu[i], sizeof(Data), 1, fp);
		}
	}
	fclose(fp);
}
/*将学生信息写入文件*/
void IO_WriteInfo()
{
	FILE *fp;
	int i;
	if ((fp = fopen("Database.txt", "w")) == NULL)
	{
		printf("\t\t\t\t打开文件失败.\n");
		return;
	}
	if (fwrite(&num, sizeof(int), 1, fp) != 1)
	{
		printf("\t\t\t\t文件写入错误.\n");
	}
	for (i = 0; i < num; i++)
	{
		if (fwrite(&stu[i], sizeof(Data), 1, fp) != 1)
		{
			printf("\t\t\t\t文件写入错误.\n");
		}
	}
	fclose(fp);
}
/*将学生信息保存为文本文件*/
void Save_stu()
{
	FILE *fp;
	int i;
	if ((fp = fopen("Save.txt", "w+")) == NULL)
	{
		printf("\t\t\t\t文件保存错误.\n");
		return;
	}
	fprintf(fp,"%10s%10s%10s%10s%10s%10s%10s%10s\n","学号","姓名","C语言","高数","英语","线代","平均成绩","名次");
	for(i=0;i<num;i++)
	{
		fprintf(fp, "%10s%10s%10.2f%10.2f%10.2f%10.2f%10.2f%10d\n", stu[i].ID, stu[i].Name, stu[i].Mark1, stu[i].Mark2, stu[i].Mark3, stu[i].Mark4, stu[i].Average,stu[i].Rank);
	}
	printf("\t\t\t\t文件保存成功.\n");
	fclose(fp);
}
/*新增学生信息*/
void Insert_stu()
{
	char x;
	int i = 1;
	while (i)
	{
		printf("\t\t\t\t当前为第%d名同学:\n", num + 1);
		printf("\t\t\t\t请输入学号:");
		scanf("%s", &stu[num].ID);
		if (ID_Different(stu[num].ID, num) == -1)
		{
			printf("\t\t\t\t该学号已存在,请重新输入.");
			getchar();
			getchar();
			break;
		}
		clear();
		printf("\t\t\t\t请输入姓名:");
		scanf("%s", &stu[num].Name);
		clear();
		stu_Input();
		stu[num].Average = Avg(stu[num]);
		num++;
		printf("\t\t\t\t输入Y继续，任意键返回上级");
		i = (x = toupper(getchar())) == 'Y' ? 1 : 0;
		clear();
	}
}
/*更改学生信息*/
void Modify_stu()
{
	while (1)
	{
		int i;
		char id[10];
		printf("\t\t\t\t请输入学号:(输入0返回上一级)");
		scanf("%s", &id);
		if (strcmp(id, "0") == 0)
			break;
		i = Search_byIndex(id);
		if (i == -1)
		{
			printf("\t\t\t\t信息不存在,请重试.\n");
			getchar();
			getchar();
			break;
		}
		else
		{
			Display_Single(i);
			printf("\t\t\t\t是否进行修改?(Y/N)");
			getchar();
			if (toupper(getchar()) == 'Y')
			{
				stu_Input();
			}
		}
	}
}
/*查找学生信息*/
void Select_stu()
{
	char id[10];
	char name[10];
	int i;
	int choice1;
	printf("\t\t\t\t请选择查找方式:\n""\t\t\t\t1.学号查找\n""\t\t\t\t2.姓名查找\n""\t\t\t\t3.返回上一级\n\t\t\t\t");
	if ((scanf("%d", &choice1)) != 1)
	{
		printf("\t\t\t\t输入错误,请重试.\n");
		return;
	}
		switch (choice1)
	{
	case 1:
		printf("\t\t\t\t请输入学号:");
		scanf("%s", &id);
		if ((i = Search_byIndex(id)) != -1)
		{
			Display_Single(i);
			getchar();
			break;
		}
		else
		{
			printf("\t\t\t\t未找到此学号的信息,请重试:\n");
			getchar();
			break;
		}
	case 2:
		printf("\t\t\t\t请输入姓名:");
		scanf("%s", &name);
		if ((i = Search_byName(name)) != -1)
		{
			Display_Single(i);
			getchar();
			break;
		}
		else
		{
			printf("\t\t\t\t未找到此学号的信息,请重试:\n");
			getchar();
			break;
		}
	case 3:
		break;
	}
	clear();
}
/*删除学生信息*/
void Delete_stu()
{
	char id[10];
	int i;
	while (1)
	{
		printf("\t\t\t\t请输入要删除的学生学号:(输入0返回上一级)");
		scanf("%s", &id);
		if (strcmp(id, "0") == 0)
			break;
		if ((i = Search_byIndex(id)) == -1)
		{
			printf("\t\t\t\t信息不存在,请重试.\n");
			getchar();
			getchar();
			break;
		}
		printf("\t\t\t\t你要删除的学生信息为:\n");
		Display_Single(i);
		printf("\t\t\t\t是否真的要删除?(Y/N)");
		getchar();
		if (toupper(getchar()) == 'Y')
		{
			for (; i < num; i++)
				stu[i] = stu[i + 1];
			printf("\t\t\t\t删除成功.\n");
			num--;
		}

	}
}
/*显示学生信息*/
void Display_stu()
{
	printf("%10s%10s%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "C语言", "高数", "英语", "线代", "平均成绩","名次");
	printf("----------------------------------------------------------------------------------------\n");
	for (int i = 0; i < num; i++)
	{
		printf("%10s%10s%10.1f%10.1f%10.1f%10.1f%10.1f%10d\n", stu[i].ID, stu[i].Name, stu[i].Mark1, stu[i].Mark2, stu[i].Mark3, stu[i].Mark4, stu[i].Average,stu[i].Rank);
	}
	getchar();
}
/*根据学号返回下标*/
int Search_byIndex(char id[])
{
	for (int i = 0; i < num; i++)
	{
		if (strcmp(stu[i].ID, id) == 0)
			return i;
	}
	return -1;
}
/*根据姓名返回下标*/
int Search_byName(char name[])
{
	for (int i = 0; i < num; i++)
	{
		if (strcmp(stu[i].Name, name) == 0)
			return i;
	}
	return -1;
}
/*显示单条学生记录*/
void Display_Single(int i)
{
	printf("%10s%10s%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "C语言", "高数", "英语", "线代", "平均成绩","名次");
	printf("----------------------------------------------------------------------------------------\n");
	printf("%10s%10s%10.1f%10.1f%10.1f%10.1f%10.1f%10d\n", stu[i].ID, stu[i].Name, stu[i].Mark1, stu[i].Mark2, stu[i].Mark3, stu[i].Mark4, stu[i].Average,stu[i].Rank);
}
/*计算各科平均成绩*/
void Average_Subject()
{
	float AvgMark1 = 0, AvgMark2 = 0, AvgMark3 = 0, AvgMark4 = 0, AvgTotal = 0;
	for (int i = 0; i < num; i++)
	{
		AvgMark1 += stu[i].Mark1;
		AvgMark2 += stu[i].Mark2;
		AvgMark3 += stu[i].Mark3;
		AvgMark4 += stu[i].Mark4;
		AvgTotal += stu[i].Average;
	}
	AvgMark1 /= num;
	AvgMark2 /= num;
	AvgMark3 /= num;
	AvgMark4 /= num;
	AvgTotal /= num;
	printf("%10s%10s%10s%10s%10s%10s\n", " ", "C语言", "高数", "英语", "线代", "平均总分");
	printf("----------------------------------------------------------------------------------------\n");
	printf("%10s%10.1f%10.1f%10.1f%10.1f%10.1f\n\n", "平均成绩", AvgMark1, AvgMark2, AvgMark3, AvgMark4, AvgTotal);
	getchar();
}
/*统计各分段的人数*/
void Mark_grade()
{
	int _90, _80, _70, _60, _50;
	_50 = _60 = _70 = _80 = _90 = 0;
	printf("\t\t%10s%10s%10s%10s%10s%10s\n", " ", "90-100", "80-89", "70-79", "60-69", "60以下");
	for (int i = 0; i < num; i++)
	{
		if (stu[i].Mark1 >= 90)
			_90++;
		else if (stu[i].Mark1 >= 80)
			_80++;
		else if (stu[i].Mark1 >= 70)
			_70++;
		else if (stu[i].Mark1 >= 60)
			_60++;
		else
			_50++;
	}
	printf("\t\t%10s%10d%10d%10d%10d%10d\n", "C语言", _90, _80, _70, _60, _50);
	_50 = _60 = _70 = _80 = _90 = 0;
	for (int i = 0; i < num; i++)
	{
		if (stu[i].Mark2 >= 90)
			_90++;
		else if (stu[i].Mark2 >= 80)
			_80++;
		else if (stu[i].Mark2 >= 70)
			_70++;
		else if (stu[i].Mark2 >= 60)
			_60++;
		else
			_50++;
	}
	printf("\t\t%10s%10d%10d%10d%10d%10d\n", "高数", _90, _80, _70, _60, _50);
	_50 = _60 = _70 = _80 = _90 = 0;
	for (int i = 0; i < num; i++)
	{
		if (stu[i].Mark3 >= 90)
			_90++;
		else if (stu[i].Mark3 >= 80)
			_80++;
		else if (stu[i].Mark3 >= 70)
			_70++;
		else if (stu[i].Mark3 >= 60)
			_60++;
		else
			_50++;
	}
	printf("\t\t%10s%10d%10d%10d%10d%10d\n", "英语", _90, _80, _70, _60, _50);
	_50 = _60 = _70 = _80 = _90 = 0;
	for (int i = 0; i < num; i++)
	{
		if (stu[i].Mark4 >= 90)
			_90++;
		else if (stu[i].Mark4 >= 80)
			_80++;
		else if (stu[i].Mark4 >= 70)
			_70++;
		else if (stu[i].Mark4 >= 60)
			_60++;
		else
			_50++;
	}
	printf("\t\t%10s%10d%10d%10d%10d%10d\n", "线代", _90, _80, _70, _60, _50);
	_50 = _60 = _70 = _80 = _90 = 0;
	for (int i = 0; i < num; i++)
	{
		if (stu[i].Average >= 90)
			_90++;
		else if (stu[i].Average >= 80)
			_80++;
		else if (stu[i].Average >= 70)
			_70++;
		else if (stu[i].Average >= 60)
			_60++;
		else
			_50++;
	}
	printf("\t\t%10s%10d%10d%10d%10d%10d\n", "平均成绩", _90, _80, _70, _60, _50);
	getchar();
}
/*学生平均分排序*/
void Reorder_stu()
{
	int i, j;
	Data temp;
	for (i = 0; i<num; i++)
	{
		temp = stu[i];
		j = i - 1;
		while (j >= 0 && temp.Average>stu[j].Average)
		{
			stu[j + 1] = stu[j];
			j--;
		}
		stu[j + 1] = temp;
	}
	stu[0].Rank = 1;
	for (int i = 1; i <= num; i++)
	{
		if (stu[i - 1].Average == stu[i].Average)
			stu[i].Rank = stu[i - 1].Rank;
		else
			stu[i].Rank = i + 1;
	}
}
/*判断学号是否重复*/
int ID_Different(char id[],int num)
{
	for (int i = 0; i < num; i++)
		if (strcmp(id, stu[i].ID) == 0)
			return -1;
}
/*按照学号排序*/
void ReorderByID()
{
	int i, j;
	Data temp;
	for (i = 0; i<num; i++)
	{
		temp = stu[i];
		j = i - 1;
		while (j >= 0 && atoi(temp.ID)<atoi(stu[j].ID))
		{
			stu[j + 1] = stu[j];
			j--;
		}
		stu[j + 1] = temp;
	}
}
/*成绩输入验证*/
int Check_Format(float Mark)
{
	float temp;
	temp = Mark - (int)Mark;
	if (temp == 0 || temp == 0.5)
		return 1;
	else
		return -1;
}
/*登陆系统*/
void Login()
{
	int i=0,choice;
	char Password[10];
	while (Log == 0)
	{
		system("cls");
		printf("\t\t\t\t学生成绩管理系统\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t\t请选择访问身份:\n""\t\t\t\t1.教师\t2.学生\n");
		printf("\t\t\t-------------------------------\n\t\t\t\t");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			while (Log == 0)
			{
				if (i >= 3)
				{
					printf("\t\t\t\t输入错误次数过多,请稍后重试.\n");
					getchar();
					exit(0);
				}
				printf("\t\t\t\t请输入密码:\n\t\t\t\t");
				scanf("%s", &Password);
				clear();
				if (strcmp(Password, "njitcs") == 0)
				{
					printf("\t\t\t\t登陆成功!\n");
					Log = 1;
					getchar();
				}
				else
				{
					printf("\t\t\t\t密码错误，请重新输入\n");
					i++;
					continue;
				}
			}
			break;
		case 2:
			Log = -1;
			break;
		default: 
			printf("\t\t\t\t输入无效，请重新输入");
			getchar();
			getchar();
			continue;
		}
	}
}
/*判断权限*/
int Available()
{
	if (Log != 1)
	{
		printf("\t\t\t\t学生无法进行本操作.\n");
		getchar();
		system("cls");
		return -1;
	}
	else
		return 1;
}
/*输入信息*/
void stu_Input()
{
	while (true)
	{
		printf("\t\t\t\t请输入C语言成绩:");
		scanf("%f", &stu[num].Mark1);
		if (stu[num].Mark1 > 100 || stu[num].Mark1 < 0)
			printf("\t\t\t\t成绩输入错误,请重试\n");
		else if (Check_Format(stu[num].Mark1) == -1)
			printf("\t\t\t\t成绩输入错误,请重试\n");
		else
			break;
	}
	clear();
	while (true)
	{
		printf("\t\t\t\t请输入高数成绩:");
		scanf("%f", &stu[num].Mark2);
		if (stu[num].Mark2 > 100 || stu[num].Mark2 < 0)
			printf("\t\t\t\t成绩输入错误,请重试\n");
		else if (Check_Format(stu[num].Mark2) == -1)
			printf("\t\t\t\t成绩输入错误,请重试\n");
		else
			break;
	}
	while (true)
	{
		printf("\t\t\t\t请输入英语成绩:");
		scanf("%f", &stu[num].Mark3);
		if (stu[num].Mark3 > 100 || stu[num].Mark3 < 0)
			printf("\t\t\t\t成绩输入错误,请重试\n");
		else if (Check_Format(stu[num].Mark3) == -1)
			printf("\t\t\t\t成绩输入错误,请重试\n");
		else
			break;
	}
	clear();
	while (true)
	{
		printf("\t\t\t\t请输入线代成绩:");
		scanf("%f", &stu[num].Mark4);
		if (stu[num].Mark4 > 100 || stu[num].Mark4 < 0)
			printf("\t\t\t\t成绩输入错误,请重试\n");
		else if (Check_Format(stu[num].Mark4) == -1)
			printf("\t\t\t\t成绩输入错误,请重试\n");
		else
			break;
	}
	clear();
}