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

constexpr auto MAX_Users = 1000;  // 假设最大学生和负责人数量
constexpr auto MAX_Competitions = 100;  // 最大竞赛项目数量

// 定义用户结构体
typedef struct {
	char id[10];
	char username[20];
	char role[20];
	char account[20];
	char password[20];
} Users;

// 声明用户数组
Users users[MAX_Users];
int num_users = 100;

// 定义管理员结构体
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Manager;

// 定义学生结构体
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Student;

// 声明学生数组
Student students[MAX_Users];
int num_students = 0;

// 定义负责人结构体
typedef struct {
	char id[20];
	char name[20];
	char password[20];
	char role[20];
} Principal;

// 声明负责人数组
Principal principals[MAX_Users];
int num_principal = 0;

// 定义竞赛项目结构体
typedef struct {
	char id[20];
	char name[100];
	char description[255];
} Competition;

// 定义学生报名信息结构体
typedef struct {
	char studentId[20];
	char competitionId[20];
	char result[100];  // 存放比赛结果，例如"未评审"、"一等奖"等
} Registration;

// 定义竞赛作品结构体
typedef struct {
	char studentId[20];  // 参赛学生ID
	char competitionId[20];  // 竞赛ID
	char workName[100];  // 作品名称
	char workDescription[255];  // 作品描述
} Work;

// 声明竞赛作品数组和计数器
Work works[MAX_Competitions];

int num_works = 0;

// 函数声明
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


//函数声明
void adminMenu();
void managerMenu();
void stdMenu();

