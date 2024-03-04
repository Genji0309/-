#include"main.h"
//用户注册
void registerUser() {
	char id[20], username[20], role[20], account[20], password[20];
	cout << "请输入ID：" << endl;
	cin >> id;
	cout << "请输入用户名：" << endl;
	cin >> username;
	cout << "请输入角色（负责人/学生）：" << endl;
	cin >> role;
	cout << "请输入账号：" << endl;
	cin >> account;
	cout << "请输入密码：" << endl;
	cin >> password;

	// 根据角色存入不同的文件
	if (strcmp(role, "学生") == 0) {
		ofstream studentFile("students.csv", ios::app);
		studentFile << id << "," << username << "," << role << "," << account << "," << password << endl;
		studentFile.close();
		num_students++;  // 更新学生数量
	}
	else if (strcmp(role, "负责人") == 0) {
		ofstream principalFile("principals.csv", ios::app);
		principalFile << id << "," << username << "," << role << "," << account << "," << password << endl;
		principalFile.close();
		num_principal++;  // 更新负责人数量
	}
	else {
		cout << "角色输入错误，请输入'负责人'或'学生'。" << endl;
	}
}



//加载用户信息
void loadUsersFromFile() {
	ifstream file("users.csv");
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string field;
		vector<string> fields;

		while (getline(ss, field, ',')) {
			fields.push_back(field);
		}

		strcpy(users[num_users].id, fields[0].c_str());
		strcpy(users[num_users].username, fields[1].c_str());
		strcpy(users[num_users].role, fields[2].c_str());
		strcpy(users[num_users].account, fields[3].c_str());
		strcpy(users[num_users].password, fields[4].c_str());

		num_users++;
	}

	file.close();
}

//添加学生信息

void addStudent() {
	if (num_students >= MAX_Users) {
		cout << "已达到最大学生数量，无法添加新的学生" << endl;
		return;
	}

	Student newStudent;
	cout << "请输入学生ID：" << endl;
	cin >> newStudent.id;
	cout << "请输入学生名称：" << endl;
	cin >> newStudent.name;
	cout << "请输入学生密码：" << endl;
	cin >> newStudent.password;
	strcpy(newStudent.role, "学生");

	students[num_students] = newStudent;
	num_students++;
}


//删除学生信息
void deleteStudent() {
	char id[20];
	cout << "请输入要删除的学生ID：" << endl;
	cin >> id;

	int i;
	for (i = 0; i < num_students; i++) {
		if (strcmp(students[i].id, id) == 0) {
			break;
		}
	}

	if (i < num_students) {
		for (int j = i; j < num_students - 1; j++) {
			students[j] = students[j + 1];
		}
		num_students--;
	}
	else {
		cout << "未找到ID为 " << id << " 的学生" << endl;
	}
}

//保存学生信息
void saveStudentsToFile() {
	ofstream file("students.csv");

	for (int i = 0; i < num_students; i++) {
		file << students[i].id << ","
			<< students[i].name << ","
			<< students[i].password << ","
			<< students[i].role << endl;
	}

	file.close();
}


//添加负责人信息
void addPrincipal() {
	if (num_principal >= MAX_Users) {
		cout << "已达到最大负责人数量，无法添加新的负责人" << endl;
		return;
	}

	Principal newPrincipal;
	cout << "请输入负责人ID：" << endl;
	cin >> newPrincipal.id;
	cout << "请输入负责人名称：" << endl;
	cin >> newPrincipal.name;
	cout << "请输入负责人密码：" << endl;
	cin >> newPrincipal.password;
	strcpy(newPrincipal.role, "负责人");

	principals[num_principal] = newPrincipal;
	num_principal++;
}


//负责人删除
void deletePrincipal() {
	char id[20];
	cout << "请输入要删除的负责人ID：" << endl;
	cin >> id;

	ifstream inFile("principals.csv");
	ofstream outFile("temp.csv");
	string line;
	bool found = false;

	while (getline(inFile, line)) {
		stringstream ss(line);
		string tempId;
		getline(ss, tempId, ',');
		if (tempId != id) {
			outFile << line << endl;
		}
		else {
			found = true;
		}
	}

	inFile.close();
	outFile.close();

	remove("principals.csv");
	rename("temp.csv", "principals.csv");

	if (!found) {
		cout << "未找到ID为 " << id << " 的负责人" << endl;
	}
	else {
		cout << "负责人信息删除成功" << endl;
	}
}

//保存负责人信息
void savePrincipalsToFile() {
	ofstream file("principals.csv");

	for (int i = 0; i < num_principal; i++) {
		file << principals[i].id << ","
			<< principals[i].name << ","
			<< principals[i].password << ","
			<< principals[i].role << endl;
	}

	file.close();
}

//加载学生信息
void loadStudentsFromFile() {
	ifstream file("students.csv");
	string line;
	num_students = 0; // 重置学生数量

	while (getline(file, line)) {
		stringstream ss(line);
		vector<string> fields;

		for (string field; getline(ss, field, ',');) {
			fields.push_back(field);
		}

		if (fields.size() >= 5) {  // 确保有足够的数据字段
			strcpy(students[num_students].id, fields[0].c_str());
			strcpy(students[num_students].name, fields[1].c_str());
			strcpy(students[num_students].password, fields[4].c_str());  // 假设密码是第五个字段
			num_students++;
		}
	}

	file.close();
}

//加载负责人信息
void loadPrincipalsFromFile() {
	ifstream file("principals.csv");
	string line;
	num_principal = 0; // 重置负责人数量

	while (getline(file, line)) {
		stringstream ss(line);
		vector<string> fields;

		for (string field; getline(ss, field, ',');) {
			fields.push_back(field);
		}

		if (fields.size() >= 5) {  // 确保有足够的数据字段
			strcpy(principals[num_principal].id, fields[0].c_str());
			strcpy(principals[num_principal].name, fields[1].c_str());
			strcpy(principals[num_principal].password, fields[4].c_str());  // 假设密码是第五个字段
			num_principal++;
		}
	}

	file.close();
}

//添加作品
void addWork() {
	if (num_works >= MAX_Competitions) {
		cout << "已达到最大作品数量，无法添加新的作品" << endl;
		return;
	}

	Work newWork;
	cout << "请输入参赛学生ID：" << endl;
	cin >> newWork.studentId;
	cout << "请输入竞赛ID：" << endl;
	cin >> newWork.competitionId;
	cout << "请输入作品名称：" << endl;
	cin >> newWork.workName;
	cout << "请输入作品描述：" << endl;
	cin >> newWork.workDescription;

	works[num_works] = newWork;
	num_works++;
}


//保存作品信息到文件中
void saveWorksToFile() {
	ofstream file("works.csv");

	for (int i = 0; i < num_works; i++) {
		file << works[i].studentId << ","
			<< works[i].competitionId << ","
			<< works[i].workName << ","
			<< works[i].workDescription << endl;
	}

	file.close();
}

//从文件中加载作品信息
void loadWorksFromFile() {
	ifstream file("works.csv");
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string field;
		vector<string> fields;

		while (getline(ss, field, ',')) {
			fields.push_back(field);
		}
		strcpy(works[num_works].studentId, fields[0].c_str());
		strcpy(works[num_works].competitionId, fields[1].c_str());
		strcpy(works[num_works].workName, fields[2].c_str());
		strcpy(works[num_works].workDescription, fields[3].c_str());
		num_works++;
	}
	file.close();
}

//竞赛报名
void registerForCompetition() {
	ofstream file("registrations.csv", ios::app); // 以追加模式打开文件
	if (!file.is_open()) {
		cout << "无法打开文件" << endl;
		return;
	}
	char studentId[20], competitionId[20];
	cout << "请输入您的学生ID: ";
	cin >> studentId;
	cout << "请输入竞赛ID: ";
	cin >> competitionId;
	// 将报名信息写入文件
	file << studentId << "," << competitionId << ",未评审\n";
	file.close();
	cout << "报名成功！" << endl;
}



//查看比赛结果
void viewResults() {
	ifstream file("results.csv");
	if (!file.is_open()) {
		cout << "无法打开文件" << endl;
		return;
	}

	char studentId[20];
	cout << "请输入您的学生ID以查看结果: ";
	cin >> studentId;

	string line;
	bool found = false;
	while (getline(file, line)) {
		stringstream ss(line);
		string tempId, competitionId, result;
		getline(ss, tempId, ',');
		getline(ss, competitionId, ',');
		getline(ss, result, ',');

		if (tempId == studentId) {
			cout << "学生ID: " << studentId << ", 竞赛ID: " << competitionId << ", 结果: " << result << endl;
			found = true;
		}
	}

	if (!found) {
		cout << "未找到学生ID为 " << studentId << " 的结果" << endl;
	}

	file.close();
}

// 负责人评分输入
void enterScores() {
	ifstream inputFile("registrations.csv");
	ofstream outputFile("results.csv", ios::app); // 以追加模式打开文件
	if (!inputFile.is_open() || !outputFile.is_open()) {
		cout << "无法打开文件" << endl;
		return;
	}

	string line;
	char studentId[20], competitionId[20], score[20];

	// 读取报名信息
	while (getline(inputFile, line)) {
		stringstream ss(line);
		string tempStudentId, tempCompetitionId;
		getline(ss, tempStudentId, ',');
		getline(ss, tempCompetitionId, ',');

		cout << "为学生ID " << tempStudentId << " 和竞赛ID " << tempCompetitionId << " 输入评分: ";
		cin >> score;

		// 将评分信息写入结果文件
		outputFile << tempStudentId << "," << tempCompetitionId << "," << score << endl;
	}

	inputFile.close();
	outputFile.close();
	cout << "评分输入完成！" << endl;
}
//发布竞赛信息
void addCompetition() {
	Competition comp;
	cout << "请输入竞赛ID: ";
	cin >> comp.id;
	cout << "请输入竞赛名称: ";
	cin >> comp.name;
	cout << "请输入竞赛描述: ";
	cin >> comp.description;

	// 写入到CSV文件
	ofstream outFile("competitions.csv", ios::app); // 以追加模式打开
	if (!outFile.is_open()) {
		cout << "无法打开文件" << endl;
		return;
	}

	outFile << comp.id << "," << comp.name << "," << comp.description << endl;
	outFile.close();

	cout << "竞赛信息发布成功！" << endl;
}

//查新学生报名信息
void manageRegistrations() {
	ifstream inFile("registrations.csv");
	if (!inFile.is_open()) {
		cout << "无法打开文件" << endl;
		return;
	}

	cout << "竞赛报名情况：" << endl;
	string line;
	while (getline(inFile, line)) {
		cout << line << endl;
	}
	inFile.close();

}



//账号登录
void login() {
	char account[20], password[20];
	bool isLoggedIn = false;
	int loginAttempts = 0;

	// 管理员账号和密码
	char adminAccount[20] = "admin";
	char adminPassword[20] = "admin123";

	loadStudentsFromFile();  // 确保加载了学生信息
	loadPrincipalsFromFile();  // 确保加载了负责人信息

	while (loginAttempts < 3 && !isLoggedIn) {
		cout << "请输入账号：" << endl;
		cin >> account;
		cout << "请输入密码：" << endl;
		cin >> password;

		// 检查管理员账户
		if (strcmp(account, adminAccount) == 0 && strcmp(password, adminPassword) == 0) {
			cout << "登录成功，欢迎管理员" << endl;
			adminMenu();  // 跳转到管理员菜单
			isLoggedIn = true;
			break;
		}

		// 检查学生账户
		if (!isLoggedIn) {
			for (int i = 0; i < num_students; i++) {
				if (strcmp(students[i].id, account) == 0 && strcmp(students[i].password, password) == 0) {
					cout << "登录成功，欢迎学生 " << students[i].name << endl;
					stdMenu();  // 跳转到学生菜单
					isLoggedIn = true;
					break;
				}
			}
		}

		// 检查负责人账户
		if (!isLoggedIn) {
			for (int i = 0; i < num_principal; i++) {
				if (strcmp(principals[i].id, account) == 0 && strcmp(principals[i].password, password) == 0) {
					cout << "登录成功，欢迎负责人 " << principals[i].name << endl;
					managerMenu();  // 跳转到负责人菜单
					isLoggedIn = true;
					break;
				}
			}
		}

		if (!isLoggedIn) {
			cout << "账号或密码错误，请重新尝试。" << endl;
			loginAttempts++;
		}
	}

	if (!isLoggedIn) {
		cout << "连续三次登录失败，程序将退出。" << endl;
		exit(1);
	}
}




// 管理员菜单函数
void adminMenu() {
	int select;
	bool isAdminMenuRunning = true;

	// 加载学生和负责人信息
	loadStudentsFromFile();
	loadPrincipalsFromFile();

	while (isAdminMenuRunning) {
		cout << "**********************" << endl;
		cout << "1. 增加学生信息" << endl;
		cout << "2. 删除学生信息" << endl;
		cout << "3. 增加竞赛负责人信息" << endl;
		cout << "4. 删除竞赛负责人信息" << endl;
		cout << "5. 查看所有学生信息" << endl;
		cout << "6. 查看所有负责人信息" << endl;
		cout << "0. 退出管理员菜单" << endl;
		cout << "**********************" << endl;
		cin >> select;
		switch (select) {
		case 1:
			addStudent();
			saveStudentsToFile();
			break;
		case 2:
			deleteStudent();
			saveStudentsToFile();
			break;
		case 3:
			addPrincipal();
			savePrincipalsToFile();
			break;
		case 4:
			deletePrincipal();
			savePrincipalsToFile();
			break;
		case 5:
			// 优化显示学生信息的格式
			cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Role" << endl;
			for (int i = 0; i < num_students; i++) {
				cout << left << setw(10) << students[i].id
					<< setw(20) << students[i].name
					<< setw(10) << students[i].role << endl;
			}
			break;
		case 6:
			// 优化显示负责人信息的格式
			cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Role" << endl;
			for (int i = 0; i < num_principal; i++) {
				cout << left << setw(10) << principals[i].id
					<< setw(20) << principals[i].name
					<< setw(10) << principals[i].role << endl;
			}
			break;
		case 0:
			isAdminMenuRunning = false;
			break;
		default:
			cout << "输入不合法，请重新输入" << endl;
			break;
		}
	}
}

// 负责人菜单
void managerMenu() {
	int select;
	bool isRunning = true; // 控制循环

	while (isRunning) {
		cout << "***************" << endl;
		cout << "1. 竞赛信息发布" << endl;
		cout << "2. 报名管理" << endl;
		cout << "3. 作品评审" << endl;
		cout << "4. 退出到主菜单" << endl;
		cout << "****************" << endl;
		cout << "请输入选项编号：";
		cin >> select;
		switch (select) {
		case 1:
			addCompetition();
			// 调用添加竞赛信息函数
			break;
		case 2:
			manageRegistrations();
			// 调用管理报名信息函数
			break;
		case 3:
			enterScores();
			// 直接调用评分输入函数
			break;
		case 4:
			isRunning = false; // 退出循环，返回主菜单
			break;
		default:
			cout << "输入不合法，请重新输入" << endl;
			break;
		}
	}
}



// 学生菜单
void stdMenu() {
	int select;
	bool isRunning = true; // 控制循环

	while (isRunning) {
		cout << "1. 竞赛报名" << endl;
		cout << "2. 提交作品" << endl;
		cout << "3. 查看结果" << endl;
		cout << "4. 退出到主菜单" << endl; // 新增选项
		cout << "请输入选项编号: ";
		cin >> select;
		switch (select) {
		case 1:
			registerForCompetition();  // 直接调用竞赛报名函数
			break;
		case 2:
			addWork();  // 直接调用添加作品函数
			break;
		case 3:
			viewResults();  // 直接调用查看结果函数
			break;
		case 4:
			isRunning = false; // 退出循环，返回主菜单
			break;
		default:
			cout << "输入不合法，请重新输入" << endl;
			break;
		}
	}
}



//主函数
int main()
{
	// 加载已注册的用户数据
	loadUsersFromFile();

	int select;

	while (true)
	{
		cout << "请选择操作：" << endl;
		cout << "1. 登录" << endl;
		cout << "2. 注册新用户" << endl;
		cout << "0. 退出系统" << endl;

		cin >> select;

		switch (select)
		{
		case 1:
			// 登录界面
			login();
			break;
		case 2:
			// 用户注册
			registerUser();
			break;
		case 0:
			// 退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
		default:
			cout << "输入不合法，请重新输入" << endl;
			system("pause");
			system("cls"); // 清屏
			break;
		}
	}
	system("cls");
	system("pause");
	return 0;
}

