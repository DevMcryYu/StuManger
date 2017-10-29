/*һ��ѧ���ɼ�����ĳ����ɼ����������ݣ�����������������ĸ�ʽ���������ݵ���Ч�ԣ�
��Ȼ��������µĹ���ʵ�֡�����Ҫ����������һ������ѡ��˵������������ܶ��ø��Եĺ���
ʵ�֣�������Ϣ���ļ����档*/
/*Ver2.0��������
1.������½ϵͳ
2.����������֤
3.֧�ֱ����ı���ʽ����
4.�����Ż�
5.�޸�һЩBug
6.�����Ż�
*/
/*ͷ�ļ�*/
#include "Head.h"
typedef struct Student Data;

/*����ṹ��*/
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
/*������*/
void main()
{
	char choice;
	IO_ReadInfo();
	Login();
	system("cls");
	while (Log!=0)
	{
		/*���˵�*/
		printf("\t\t\t--------ѧ���ɼ�����ϵͳ--------\n");
		printf("\t\t\t        1.����ѧ���ɼ�\n");
		printf("\t\t\t        2.ɾ��ѧ���ɼ�\n");
		printf("\t\t\t        3.����ѧ���ɼ�\n");
		printf("\t\t\t        4.��ѯѧ���ɼ�\n");
		printf("\t\t\t        5.��ӡѧ���ɼ�\n");
		printf("\t\t\t        6.����ƽ���ɼ�\n");
		printf("\t\t\t        7.ѧ���ɼ�����\n");
		printf("\t\t\t        8.������������\n");
		printf("\t\t\t        9.�˳�����ϵͳ\n");
		printf("\t\t\t--------------------------------\n");
		printf("\t\t\t\t��������ż���:");
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
					printf("\t\t\t\t\t������Ч��������ѡ��:\n");
					continue;
				 }
		}
		IO_WriteInfo();
	}
}
/*��ɼ�ƽ��ֵ*/
float Avg(Data stu)
{
	return (stu.Mark1 + stu.Mark2 + stu.Mark3 + stu.Mark4) / 4;
}
/*���������*/
void clear()
{
	while (getchar() != '\n')
		continue;
}
/*��ѧ����Ϣ���ļ�����*/
void IO_ReadInfo()
{
	FILE *fp;
	int i;
	if ((fp = fopen("Database.txt", "r")) == NULL)
	{
		printf("\t\t\t\t�ļ���ʧ��.\n");
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
/*��ѧ����Ϣд���ļ�*/
void IO_WriteInfo()
{
	FILE *fp;
	int i;
	if ((fp = fopen("Database.txt", "w")) == NULL)
	{
		printf("\t\t\t\t���ļ�ʧ��.\n");
		return;
	}
	if (fwrite(&num, sizeof(int), 1, fp) != 1)
	{
		printf("\t\t\t\t�ļ�д�����.\n");
	}
	for (i = 0; i < num; i++)
	{
		if (fwrite(&stu[i], sizeof(Data), 1, fp) != 1)
		{
			printf("\t\t\t\t�ļ�д�����.\n");
		}
	}
	fclose(fp);
}
/*��ѧ����Ϣ����Ϊ�ı��ļ�*/
void Save_stu()
{
	FILE *fp;
	int i;
	if ((fp = fopen("Save.txt", "w+")) == NULL)
	{
		printf("\t\t\t\t�ļ��������.\n");
		return;
	}
	fprintf(fp,"%10s%10s%10s%10s%10s%10s%10s%10s\n","ѧ��","����","C����","����","Ӣ��","�ߴ�","ƽ���ɼ�","����");
	for(i=0;i<num;i++)
	{
		fprintf(fp, "%10s%10s%10.2f%10.2f%10.2f%10.2f%10.2f%10d\n", stu[i].ID, stu[i].Name, stu[i].Mark1, stu[i].Mark2, stu[i].Mark3, stu[i].Mark4, stu[i].Average,stu[i].Rank);
	}
	printf("\t\t\t\t�ļ�����ɹ�.\n");
	fclose(fp);
}
/*����ѧ����Ϣ*/
void Insert_stu()
{
	char x;
	int i = 1;
	while (i)
	{
		printf("\t\t\t\t��ǰΪ��%d��ͬѧ:\n", num + 1);
		printf("\t\t\t\t������ѧ��:");
		scanf("%s", &stu[num].ID);
		if (ID_Different(stu[num].ID, num) == -1)
		{
			printf("\t\t\t\t��ѧ���Ѵ���,����������.");
			getchar();
			getchar();
			break;
		}
		clear();
		printf("\t\t\t\t����������:");
		scanf("%s", &stu[num].Name);
		clear();
		stu_Input();
		stu[num].Average = Avg(stu[num]);
		num++;
		printf("\t\t\t\t����Y����������������ϼ�");
		i = (x = toupper(getchar())) == 'Y' ? 1 : 0;
		clear();
	}
}
/*����ѧ����Ϣ*/
void Modify_stu()
{
	while (1)
	{
		int i;
		char id[10];
		printf("\t\t\t\t������ѧ��:(����0������һ��)");
		scanf("%s", &id);
		if (strcmp(id, "0") == 0)
			break;
		i = Search_byIndex(id);
		if (i == -1)
		{
			printf("\t\t\t\t��Ϣ������,������.\n");
			getchar();
			getchar();
			break;
		}
		else
		{
			Display_Single(i);
			printf("\t\t\t\t�Ƿ�����޸�?(Y/N)");
			getchar();
			if (toupper(getchar()) == 'Y')
			{
				stu_Input();
			}
		}
	}
}
/*����ѧ����Ϣ*/
void Select_stu()
{
	char id[10];
	char name[10];
	int i;
	int choice1;
	printf("\t\t\t\t��ѡ����ҷ�ʽ:\n""\t\t\t\t1.ѧ�Ų���\n""\t\t\t\t2.��������\n""\t\t\t\t3.������һ��\n\t\t\t\t");
	if ((scanf("%d", &choice1)) != 1)
	{
		printf("\t\t\t\t�������,������.\n");
		return;
	}
		switch (choice1)
	{
	case 1:
		printf("\t\t\t\t������ѧ��:");
		scanf("%s", &id);
		if ((i = Search_byIndex(id)) != -1)
		{
			Display_Single(i);
			getchar();
			break;
		}
		else
		{
			printf("\t\t\t\tδ�ҵ���ѧ�ŵ���Ϣ,������:\n");
			getchar();
			break;
		}
	case 2:
		printf("\t\t\t\t����������:");
		scanf("%s", &name);
		if ((i = Search_byName(name)) != -1)
		{
			Display_Single(i);
			getchar();
			break;
		}
		else
		{
			printf("\t\t\t\tδ�ҵ���ѧ�ŵ���Ϣ,������:\n");
			getchar();
			break;
		}
	case 3:
		break;
	}
	clear();
}
/*ɾ��ѧ����Ϣ*/
void Delete_stu()
{
	char id[10];
	int i;
	while (1)
	{
		printf("\t\t\t\t������Ҫɾ����ѧ��ѧ��:(����0������һ��)");
		scanf("%s", &id);
		if (strcmp(id, "0") == 0)
			break;
		if ((i = Search_byIndex(id)) == -1)
		{
			printf("\t\t\t\t��Ϣ������,������.\n");
			getchar();
			getchar();
			break;
		}
		printf("\t\t\t\t��Ҫɾ����ѧ����ϢΪ:\n");
		Display_Single(i);
		printf("\t\t\t\t�Ƿ����Ҫɾ��?(Y/N)");
		getchar();
		if (toupper(getchar()) == 'Y')
		{
			for (; i < num; i++)
				stu[i] = stu[i + 1];
			printf("\t\t\t\tɾ���ɹ�.\n");
			num--;
		}

	}
}
/*��ʾѧ����Ϣ*/
void Display_stu()
{
	printf("%10s%10s%10s%10s%10s%10s%10s%10s\n", "ѧ��", "����", "C����", "����", "Ӣ��", "�ߴ�", "ƽ���ɼ�","����");
	printf("----------------------------------------------------------------------------------------\n");
	for (int i = 0; i < num; i++)
	{
		printf("%10s%10s%10.1f%10.1f%10.1f%10.1f%10.1f%10d\n", stu[i].ID, stu[i].Name, stu[i].Mark1, stu[i].Mark2, stu[i].Mark3, stu[i].Mark4, stu[i].Average,stu[i].Rank);
	}
	getchar();
}
/*����ѧ�ŷ����±�*/
int Search_byIndex(char id[])
{
	for (int i = 0; i < num; i++)
	{
		if (strcmp(stu[i].ID, id) == 0)
			return i;
	}
	return -1;
}
/*�������������±�*/
int Search_byName(char name[])
{
	for (int i = 0; i < num; i++)
	{
		if (strcmp(stu[i].Name, name) == 0)
			return i;
	}
	return -1;
}
/*��ʾ����ѧ����¼*/
void Display_Single(int i)
{
	printf("%10s%10s%10s%10s%10s%10s%10s%10s\n", "ѧ��", "����", "C����", "����", "Ӣ��", "�ߴ�", "ƽ���ɼ�","����");
	printf("----------------------------------------------------------------------------------------\n");
	printf("%10s%10s%10.1f%10.1f%10.1f%10.1f%10.1f%10d\n", stu[i].ID, stu[i].Name, stu[i].Mark1, stu[i].Mark2, stu[i].Mark3, stu[i].Mark4, stu[i].Average,stu[i].Rank);
}
/*�������ƽ���ɼ�*/
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
	printf("%10s%10s%10s%10s%10s%10s\n", " ", "C����", "����", "Ӣ��", "�ߴ�", "ƽ���ܷ�");
	printf("----------------------------------------------------------------------------------------\n");
	printf("%10s%10.1f%10.1f%10.1f%10.1f%10.1f\n\n", "ƽ���ɼ�", AvgMark1, AvgMark2, AvgMark3, AvgMark4, AvgTotal);
	getchar();
}
/*ͳ�Ƹ��ֶε�����*/
void Mark_grade()
{
	int _90, _80, _70, _60, _50;
	_50 = _60 = _70 = _80 = _90 = 0;
	printf("\t\t%10s%10s%10s%10s%10s%10s\n", " ", "90-100", "80-89", "70-79", "60-69", "60����");
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
	printf("\t\t%10s%10d%10d%10d%10d%10d\n", "C����", _90, _80, _70, _60, _50);
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
	printf("\t\t%10s%10d%10d%10d%10d%10d\n", "����", _90, _80, _70, _60, _50);
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
	printf("\t\t%10s%10d%10d%10d%10d%10d\n", "Ӣ��", _90, _80, _70, _60, _50);
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
	printf("\t\t%10s%10d%10d%10d%10d%10d\n", "�ߴ�", _90, _80, _70, _60, _50);
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
	printf("\t\t%10s%10d%10d%10d%10d%10d\n", "ƽ���ɼ�", _90, _80, _70, _60, _50);
	getchar();
}
/*ѧ��ƽ��������*/
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
/*�ж�ѧ���Ƿ��ظ�*/
int ID_Different(char id[],int num)
{
	for (int i = 0; i < num; i++)
		if (strcmp(id, stu[i].ID) == 0)
			return -1;
}
/*����ѧ������*/
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
/*�ɼ�������֤*/
int Check_Format(float Mark)
{
	float temp;
	temp = Mark - (int)Mark;
	if (temp == 0 || temp == 0.5)
		return 1;
	else
		return -1;
}
/*��½ϵͳ*/
void Login()
{
	int i=0,choice;
	char Password[10];
	while (Log == 0)
	{
		system("cls");
		printf("\t\t\t\tѧ���ɼ�����ϵͳ\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t\t��ѡ��������:\n""\t\t\t\t1.��ʦ\t2.ѧ��\n");
		printf("\t\t\t-------------------------------\n\t\t\t\t");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			while (Log == 0)
			{
				if (i >= 3)
				{
					printf("\t\t\t\t��������������,���Ժ�����.\n");
					getchar();
					exit(0);
				}
				printf("\t\t\t\t����������:\n\t\t\t\t");
				scanf("%s", &Password);
				clear();
				if (strcmp(Password, "njitcs") == 0)
				{
					printf("\t\t\t\t��½�ɹ�!\n");
					Log = 1;
					getchar();
				}
				else
				{
					printf("\t\t\t\t�����������������\n");
					i++;
					continue;
				}
			}
			break;
		case 2:
			Log = -1;
			break;
		default: 
			printf("\t\t\t\t������Ч������������");
			getchar();
			getchar();
			continue;
		}
	}
}
/*�ж�Ȩ��*/
int Available()
{
	if (Log != 1)
	{
		printf("\t\t\t\tѧ���޷����б�����.\n");
		getchar();
		system("cls");
		return -1;
	}
	else
		return 1;
}
/*������Ϣ*/
void stu_Input()
{
	while (true)
	{
		printf("\t\t\t\t������C���Գɼ�:");
		scanf("%f", &stu[num].Mark1);
		if (stu[num].Mark1 > 100 || stu[num].Mark1 < 0)
			printf("\t\t\t\t�ɼ��������,������\n");
		else if (Check_Format(stu[num].Mark1) == -1)
			printf("\t\t\t\t�ɼ��������,������\n");
		else
			break;
	}
	clear();
	while (true)
	{
		printf("\t\t\t\t����������ɼ�:");
		scanf("%f", &stu[num].Mark2);
		if (stu[num].Mark2 > 100 || stu[num].Mark2 < 0)
			printf("\t\t\t\t�ɼ��������,������\n");
		else if (Check_Format(stu[num].Mark2) == -1)
			printf("\t\t\t\t�ɼ��������,������\n");
		else
			break;
	}
	while (true)
	{
		printf("\t\t\t\t������Ӣ��ɼ�:");
		scanf("%f", &stu[num].Mark3);
		if (stu[num].Mark3 > 100 || stu[num].Mark3 < 0)
			printf("\t\t\t\t�ɼ��������,������\n");
		else if (Check_Format(stu[num].Mark3) == -1)
			printf("\t\t\t\t�ɼ��������,������\n");
		else
			break;
	}
	clear();
	while (true)
	{
		printf("\t\t\t\t�������ߴ��ɼ�:");
		scanf("%f", &stu[num].Mark4);
		if (stu[num].Mark4 > 100 || stu[num].Mark4 < 0)
			printf("\t\t\t\t�ɼ��������,������\n");
		else if (Check_Format(stu[num].Mark4) == -1)
			printf("\t\t\t\t�ɼ��������,������\n");
		else
			break;
	}
	clear();
}