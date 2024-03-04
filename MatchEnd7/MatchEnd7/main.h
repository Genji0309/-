#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<cstring>
#include<iomanip>

using namespace std;

constexpr auto MAX_Users = 1000;  // �������ѧ���͸���������
constexpr auto MAX_Competitions = 100;  // �������Ŀ����

// �����û��ṹ��
typedef struct {
	char id[10];
	char username[20];
	char role[20];
	char account[20];
	char password[20];
} Users;

// �����û�����
Users users[MAX_Users];
int num_users = 100;

// �������Ա�ṹ��
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Manager;

// ����ѧ���ṹ��
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Student;

// ����ѧ������
Student students[MAX_Users];
int num_students = 0;

// ���帺���˽ṹ��
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Principal;

// ��������������
Principal principals[MAX_Users];
int num_principal = 0;

// ���徺����Ŀ�ṹ��
typedef struct {
	char id[20];
	char name[100];
	char description[255];
} Competition;

// ����ѧ��������Ϣ�ṹ��
typedef struct {
	char studentId[20];
	char competitionId[20];
	char result[100];  // ��ű������������"δ����"��"һ�Ƚ�"��
} Registration;

// ���徺����Ʒ�ṹ��
typedef struct {
	char studentId[20];  // ����ѧ��ID
	char competitionId[20];  // ����ID
	char workName[100];  // ��Ʒ����
	char workDescription[255];  // ��Ʒ����
} Work;

// ����������Ʒ����ͼ�����
Work works[MAX_Competitions];

int num_works = 0;

// ��������
void adminMenu();
void managerMenu();
void stdMenu();
void registerUser();
void loadUsersFromFile();
void addStudent();
void deleteStudent();
void saveStudentsToFile();
void loadStudentsFromFile();
void addPrincipal();
void deletePrincipal();
void savePrincipalsToFile();
void loadPrincipalsFromFile();
void login();
void addWork();
void saveWorksToFile();
void loadWorksFromFile();


//��������
void adminMenu();
void managerMenu();
void stdMenu();

