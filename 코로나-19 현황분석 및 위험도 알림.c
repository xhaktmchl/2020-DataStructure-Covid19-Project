#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//노드 정의
typedef struct Node //노드 정의
{
	struct Node* prev; //prev 노드
	int name; //확진번호 변수
	char *sex; //성별 변수
	int age; //나이 변수
	char* loc; //거주지 변수
	char* death; //사망 유무 변수
	struct Node* next; //next 노드
}Node; //노드의 이름을 Node 라 정의



//노드 할당 함수
Node* getNode(Node** q)//노드 할당 및 노드의 주소 반환
{
	(*q) = (Node*)malloc(sizeof(Node)); //새로운 노드 할당
	(*q)->prev = NULL; // prev 공간 초기화
	(*q)->next = NULL; // next 공간 초기화

	return (*q); // 할당받은 노드 반환
}

//확진자 추가
void add(Node** H,int name,char *sex,int age,char* loc,char* death,int deathN, int r) //add함수로 확진번호,성별 포인터배열,나이, 거주지 포인터 배열, 사망유무 포인터 배열,사망유무 수, 추가할 명단의 순서
{
	int cnt = 0,i; // cnt는 확진자의 수
	Node* p = getNode(&p);  // p노드 할당
	Node* new = getNode(&new); //정보를 저장할 새 노드 할당

	//저장할 정보 저장
	new->name = name; // 확진번호 저장
	new->sex = sex; // 성별 저장
	new->age = age; // 나이 저장
	new->death = death; // 사망유무 저장
	new->loc = loc;// 거주지 저장

	//확진번호 오류검사
	for (i = 0; i < 2; i++) { //for 반복문으로 
		p = H[i]; //p 에 명단의 헤더노드 저장

		//데이터 개수 세기
		while (1) // 반복문으로
		{
			p = p->next; //다음 노드로 넘어가고
			if ((p->next) == NULL) { break; } // 마지막 노드 이면 중단
			if (p->name == name) { printf("이미 등록된 확진번호 입니다. 다시 시도 해주십시오.\n"); return; } //이미 등록된 번호면 끝냄
			cnt++; // 확진자 수 측정
		}

		//r값  오류 검사
		if (i == deathN) { //i가 추가하고자 하는 리스트의 인덱스 일 때
			//순위 에러 조건
			if (r<1 || r>cnt + 1) { printf("명단에 삽입할 위치가 틀렸습니다!! 다시 시도해주십시오. \n"); return; } //r이1보다 작거나 (노드의 개수+1)개 보다 크면 무효화 
		}
	}
	
		
			p = H[deathN]; // p위치 헤더위치로 저장
			cnt = 0; // 노드의 개수 0 으로 초기화

			//r번째 까지 탐색
			for (i = 0; i < r; i++) // 사망 또는 생존 리스트의 처음 부터 끝까지 반복
			{
				p = p->next; cnt++; // 다음노드로 넘어감 및 노드의 개수 증가
				if (cnt == r) //r번째 노드이면 
				{
					new->next = p; //삽입 노드의 다음이 r번째 노드 가리킴
					new->prev = p->prev; //삽입노드의 뒤가 r-1번째 노드 가리킴

					p->prev->next = new; //r-1번째 노드의 다음이 삽입노드 가리킴
					p->prev = new;  // r번째 노드의 뒤가 삽입노드 가리킴
				}

			}
		
}



//통계 및 위험한 곳 출력 함수
void printWarning(Node** H, Node** T,char **sex, char **loc, char** death) // 헤더노드, 트레일러 노드, 성별 포인터 배열, 거주지 포인터 배열 인자로 받음
{
	int gid,i,j; // 그룹 인덱스 gid
	Node* p = getNode(&p); // p노드 할당
	int maleSum = 0, femaleSum = 0, ageSum = 0, locSum[6] = { 0 }, c = 0, tp=0 , locSumR[6] = { 0 ,1,2,3,4,5 }; // 남성의 수 ,여성의 수 ,나이의 합, 각 거주지의 확진자 수,거주지 배열의 인덱스 배열 선언
	int sexN = 0,locN=0,deathN=0; // 성별 배열의 인덱스 , 거주지 배열의 인덱스 ,사망유무 배열의 인덱스 선언
	int dc = 0; // 사망자 수 dc

	printf("명단을 출력하겠습니다.\n\n"); //명단출력 안내문

	// 각 리스트 탐색
	for (gid = 0; gid < 2; gid++) //반복문으로 사망 리스트, 생존 리스트 탐색
	{
		p = H[gid]; // 리스트의 헤더노드 가리킴
		while (1) //계속 반복 한다
		{
			p = p->next; //p가 다음 노드 가리킴
			if (p == T[gid]) { break; } // p가 리스트의 트레일러 노드를 가리키면 반복 중단

			printf("확진 번호: %d // ", p->name); //확진번호 출력
			printf("성별: %s // ", p->sex); // 성별 출력
			printf("나이: %d세 // ", p->age); // 나이 출력
			printf("거주지: %s // ", p->loc); // 거주지 출력
			printf("%s ", p->death); // 사망유무 출력
			printf("\n"); //다음줄로 넘어감
			
			if (strcmp(p->sex, sex[0]) == 0) { maleSum++; } // 남성이면 maleSum 증가
			else if (strcmp(p->sex, sex[1]) == 0) { femaleSum++; } // 여성이면 famaleSum 증가

			if (strcmp(p->death, death[0]) == 0) { dc++; } // 사망자 이면 사망자 수 증가

			ageSum += p->age; //ageSum에 나이를 합한다
			for (locN = 0; locN < 6; locN++) // 거주지 인덱스 가 0부터 6까지 증가하면서
			{
				if (strcmp(loc[locN], p->loc) == 0) { locSum[locN]++; } // 각 거주지 확진자수 증가
			}
			
			
			
			c++; //총 인원 수 증가
		}
		
	}printf("\n"); //다음줄로 넘어감
	
	//통계결과 출력
	printf("통계치를 출력하겠습니다.\n\n"); // 통계출력 안내문
	printf("확진자 수:\n 남: %d명 여: %d명 으로 총 %d명 입니다.\n\n", maleSum, femaleSum, maleSum+ femaleSum); // 남성 여성 및 총 확진자 수 출력
	printf("사망자수: 확진자 %d 명 중 %d 명이 사망했습니다. \n 따라서 사망률은 %.1f %% 이므로 주의하십시오\n\n",c,dc, ((float)dc / c) * 100); // 사망률 출력
	printf("확진자들의 평균 나이는 %.1f세 입니다.\n\n", (float)ageSum / c); // 확진자 나이의 평균 출력
	printf("지역별 확진자 수:\n서울 %d명\n경기 %d명\n강원 %d명\n충청 %d명\n경상 %d명\n전라 %d명 입니다.\n\n", locSum[0], locSum[1], locSum[2], locSum[3], locSum[4], locSum[5]); //각 지역의 확진자 수 출력
	
	//확진자 거주지 인덱스 내림차순으로 정렬

	for (i = 0; i < 6; i++) // 이중 
	{
		for ( j = 0; j < 5; j++)// 반복문으로 
		{
			if (locSum[j] <= locSum[j + 1]) // j번째 지역의 확진자 수가 j+1 번째 지역의 확진자 수보다 적거나 같으면
			{
				tp = locSumR[j]; // tp 변수에 j번째 거주지 배열의 인덱스 저장 
				locSumR[j] = locSumR[j + 1]; // j번째 거주지 배열의 인덱스에 j+1번째 거주지 배열의 인덱스 저장
				locSumR[j + 1] = tp; //j+1번째 거주지 배열의 인덱스에 tp값 저장

				tp = locSum[j]; // tp 변수에 j번째 거주지 인원수  저장 
				locSum[j] = locSum[j + 1]; // j번째 거주지 인원수 배열에 j+1번째 거주지 인원수 배열 저장
				locSum[j + 1] = tp; //j+1번째 거주지 인원수 배열에 tp값 저장
			}
		}
	}
	
	//위험한 지역 출력
	printf("특히 "); //특히
	for (i = 0; i < 3; i++) { //반복문으로 
		
			printf(" %s ", loc[locSumR[i]]); // 확진자수 가장 많은 세개 지역 출력
		
	}
	printf("순으로 세 지역의 발병률이 제일 높으므로 이지역에 사는 사람은 외출금지 등 신중한 행동이 요구됩니다. \n"); // 주의 문구 출력
	printf("\n\n"); //다음줄로 넘어감
	

}


//확진번호로 검색 
void getName(Node** H, Node** T,  int name) // 확진번호로 검색하는 getName 함수
{
	Node* p =getNode(&p); // p에 노드 할당
	int c = 0; // 확진자가 검색된 횟수 선언


	for (int gid = 0; gid < 2; gid++) // gid를 반복문으로 증가시키면서
	{
		p = H[gid]; // p에 리스트 헤더노드 저장
		while (1) // 계속 반복
		{
			p = p->next; //p가 다음 노드 가리킴
			if (gid == 1 && p == T[gid] && c == 0) { printf("등록된 확진번호를 찾을 수 없습니다. \n"); } // 마지막 리스트 까지 다 돌았을 때 검색한 확진자가 없을 경우
			if (gid==0 && p == T[gid]) { break; } //첫번째 리스트 마지막 이면 반복 중단
			if (gid == 1 && p == T[gid]) { return; } // 두번째 리스트 마지막이면 함수 중단
			if (name == p->name)  //검색번호랑 확진자 번호랑 같으면
			{
				printf("확진 번호: %d //", p->name); // 확진번호 출력
				printf("성별: %s //", p->sex); // 성별 출력
				printf("나이: %d세 //", p->age); // 나이 출력
				printf("거주지: %s //", p->loc); // 거주지 출력
				printf("%s ", p->death); // 사망유무 출력
				printf("\n"); // 다음줄로 넘어감
				c++; // 확지자가 검색된 횟수 증가 
			}
		}
	}printf("\n"); //다음줄로 넘어감
}

//성별로 검색 
void getSex(Node** H, Node** T,  char** sex, int sexN) // 성별로 검색하는 getSex 함수
{
	Node* p =getNode(&p); // p 노드 할당


	for (int gid = 0; gid < 2; gid++) // gid를 반복문으로 증가
	{

		p = H[gid]; // p가 리스트의 헤더노드 가리킴
		while (1) // 계속 반복
		{
			p = p->next; //p가 다음 노드 가리킴
			if (gid == 0 && p == T[gid]) { break; } //첫번째 리스트 마지막 이면 반복 중단
			if (gid == 1 && p == T[gid]) { return; }  // 두번째 리스트 마지막이면 함수 중단
			if (strcmp(sex[sexN], p->sex) == 0)  //검색 성별과 확진자 성별이 같으면
			{
				printf("확진 번호: %d //", p->name); // 확진번호 출력
				printf("성별: %s //", p->sex); // 성별 출력
				printf("나이: %d세 //", p->age); // 나이 출력
				printf("거주지: %s //", p->loc); // 거주지 출력
				printf("%s ", p->death); // 사망유무 출력
				printf("\n");  // 다음줄로 넘어감
			}
		}


	}printf("\n"); //다음줄로 넘어감
}

//거주지 검색
void getLoc(Node** H, Node** T, char** loc, int locN) //거주지를 검색하는 getLoc 함수 
{
	Node* p = getNode(&p); // p 노드 할당
	for (int gid = 0; gid < 2; gid++) // gid를 반복문으로 증가
	{
		p = H[gid]; // p가 리스트의 헤더노드 가리킴
		while (1) // 계속 반복
		{
			p = p->next; //p가 다음 노드 가리킴
			if (gid == 0 && p == T[gid]) { break; }  //첫번째 리스트 마지막 이면 반복 중단
			if (gid == 1 && p == T[gid]) { return; } // 두번째 리스트 마지막이면 함수 중단
			if (strcmp(loc[locN], p->loc) == 0)  //검색거주지와 확진자 거주지 같으면
			{
				printf("확진 번호: %d //", p->name); // 확진번호 출력
				printf("성별: %s //", p->sex); // 성별 출력
				printf("나이: %d세 //", p->age); // 나이 출력
				printf("거주지: %s //", p->loc); // 거주지 출력
				printf("%s ", p->death); // 사망유무 출력
				printf("\n"); // 다음줄로 넘어감
			}
		}
	}printf("\n"); //다음줄로 넘어감
}


//삭제
void delete(Node** H, Node** T) //delete 함수
{
	Node* p = getNode(&p); // p 노드 선언및 할당
	int gid,name; // 그룹 인덱스 gid , 입력할 확진번호 name

	printf("삭제할 확진번호를 입력하세요:  "); //삭제 안내문 출력
	scanf("%d", &name); //삭제할 확진번호 입력

	for (gid = 0; gid < 2; gid++) // 반복문으로 gid를 증가시키면서
	{
		p = H[gid]; // p에 리스트 헤더노드 저장

		while (1) // 계속 반복
		{
			p = p->next; // p가 다음 노드 가리킴
			if (p == T[gid]) // p가 리스트의 마지막 노드일때
			{
				if (gid == 0) { break; } // 첫번째 리스트일때 반목문 탈출
				else if (gid == 1) { printf("삭제하고자 하는 확진번호가 없습니다. \n"); return; } //두번째 리스트 일때 삭제한 번호 없으면 안내하고 함수 종료
			}
			if (p->name == name) // 삭제하고자 하는 확진번호랑 p의 확진번호가 같으면
			{ 
				printf(" %d번 확진자가 삭제 되었습니다.\n",p->name); // 삭제될 확진번호 안내 출력
				
				p->prev->next = p->next; // p의 전 노드가 p의 뒤 노드 가리킴
				p->next->prev = p->prev; // p의 뒤 노드가 p의 전 노드 가리킴

				free(p); // p노드 삭제
				return; // 함수 종료
			}
		}
	}printf("\n"); //다음줄로 넘어감
	
	
}



int main() //메인 함수
{
	Node* H[2], * T[2]; // 각 두개씩의 헤더와 트레일러 포인터 배열 구조체 선언
	int i,gid=0,r; //gid는 그룹 인덱스, r은 추가위치 변수 선언
	int name, age ; // 확진번호와 나이 변수선언
	char oper; // 명령어 변수
	int sexN,deathN,locN ,getN; // sexN,deathN,locN 는 성별,사망유무,거주지 포인터 배열의 인덱스 선언 
	char* sex[2] = { "Male","Female" }, * death[2] = { "사망","생존" }; //성, 사망유무 포인터 배열 선언
	char* loc[6] = { "서울","경기","강원","충청","경상","전라" }; // 거주지 포인터 배열 선언 및 초기화


	//헤더 트레일러 할당 및 초기화
	for (gid = 0; gid < 2; gid++) // 반복문으로 gid를 증가시키면서
	{
		H[gid] = getNode(&H[gid]); // 리스트의 헤더노드 할당 및 초기화
		T[gid] = getNode(&T[gid]); // 리스트의 트레일러 노드 할당 및 초기화

		H[gid]->next = T[gid]; // 헤더노드가 트레일러 노드 가리킴
		T[gid]->prev = H[gid]; // 트레일러 노드가 헤더노드 가리킴
	}
	Node* p = getNode(&p); // p노드 할당 및 초기화


	//미리 10 명의 확진자 저장
	add(&H, 1, sex[0], 21, loc[4], death[1], 1, 1); // 1번 확진자  저장
	add(&H, 2, sex[0], 20, loc[4], death[1], 1, 1); // 2번 확진자  저장
	add(&H, 3, sex[0], 34, loc[4], death[1], 1, 1); // 3번 확진자  저장
	add(&H, 4, sex[0], 59, loc[4], death[0], 0, 1); // 4번 확진자  저장
	add(&H, 5, sex[1], 15, loc[1], death[1], 1, 1); // 5번 확진자  저장
	add(&H, 6, sex[1], 26, loc[1], death[0], 0, 1); // 6번 확진자  저장
	add(&H, 7, sex[1], 27, loc[0], death[1], 1, 1); // 7번 확진자  저장
	add(&H, 8, sex[1], 50, loc[0], death[1], 1, 1); // 8번 확진자  저장
	add(&H, 9, sex[0], 72, loc[2], death[0], 0, 1); // 9번 확진자  저장
	add(&H, 10, sex[1], 27, loc[3], death[1], 1, 1); // 10번 확진자  저장
	
	
	
	//입력
	while (1) // 계속반복
	{
		printf("명령을 입력 하시오 : (add : A ,delete : D, get : G , printWarning: W 대문자 입력)  \n"); // 명령 oper 안내문
		scanf("%c", &oper); // 명령 oper 입력
		if(oper!='A' && oper!='D' && oper!='G' &&  oper!= 'W') // oper명령이 잘못 입력되면
		{
			printf("명령을 잘못 입력했습니다! \n"); getchar();  continue; // 잘못된 안내문 출력
		}

		//인원 추가
		if (oper == 'A') // A 명령을 입력한 경우
		{ //A일때 add
			printf("인원 정보 입력을 해주십시오\n"); //인원정보 입력 안내문
			printf("확진 번호: ");  scanf("%d", &name); // 추가할 확진 번호 name 입력
			printf("\n성별 : (0.남 , 1.여 숫자를 고르시오) "); scanf("%d", &sexN); // 성별 sexN 입력
			if (sexN != 0 && sexN != 1) { printf("성별을 잘못 입력했습니다!! 다시 시도해주십시오 \n"); getchar();  continue; } // 성별번호 잘못 입력한 경우 안내문 출력

			printf("\n나이:  "); scanf("%d", &age); // 나이 age 입력
			if (age <= 0 || age > 200) { printf("나이를 잘못 입력하셨습니다!! 다시 시도해주십시오 \n"); getchar(); continue; } // 나이를 잘못 입력한 경우 안내문 출력


			printf("\n거주지 : ( 0.서울 , 1.경기, 2.강원, 3.충청, 4.경상, 5.전라  숫자 입력 \n"); // 거주지 번호 안내문
			scanf("%d", &locN); // 거주지 번호 locN  입력
			if (locN != 0 && locN != 1 && locN != 2 && locN != 3 && locN != 4 && locN != 5) { printf("거주지를 잘못 입력했습니다!! 다시 시도해주십시오 \n"); getchar();  continue; } //거주지 번호  발못 입력한 경우 안내문 출력
			
			printf("\n사망 여부 : (0.사망, 1.생존 ) 입력 \n"); scanf("%d", &deathN); // 사망여부 deathN 입력
			if (deathN != 0 && deathN != 1) { printf("사망 유무를 잘못 입력했습니다!! 다시 시도해주십시오 \n"); getchar(); continue; } // 사망유무 잘못 입력한 경우
			
			printf("\n삽입할 위치(숫자입력) :  "); scanf("%d", &r); getchar();//추가할 위치 r 입력
			add(&H, name, sex[sexN], age, loc[locN], death[deathN], deathN, r); // add함수 호출로 입력한 확진자 추가
		}
	
	
		
		//검색
		else if (oper == 'G') //G명령을 입력한 경우
		{
			printf("무엇을 검색할 지 번호를 선택하세요\n"); // 검색 명령 고르기
			printf("0.확진번호 1.성별 2.거주지  "); scanf("%d", &getN); // 검색할 목록번호 getN  입력 

			if (getN != 0 && getN != 1 && getN != 2) { // getN 잘못 입력한 경우
				printf("잘못 입력 하셨습니다. 다시시도해주십시오\n"); // 잘못됨 알려주기
			}

			if (getN == 0) //확진번호로 검색
			{ 
				printf("확진번호를 입력하세요: ");  scanf("%d", &name); //검색할 확진번호 입력
				
					getName(&H, &T, name); // getName 함수 호출로 검색한 확진번호의 확진자 출력
			}

			if (getN == 1)//성별로 검색
			{
				printf("성별 번호를 고르세요: 0.남 1.여 ");  scanf("%d", &sexN); //검색할 성별 번호로 입력
				if (sexN != 0 && sexN != 1) { printf("성별을 잘못 입력했습니다!! 다시 시도해주십시오 \n"); getchar(); continue; } // 잘못된 번호 입력할 경우 처음으로 돌아감
					getSex(&H, &T, &sex,sexN); // getSex 함수 호출로 검색한 성별의 확진자 출력
			}

			if (getN == 2) //거주지로 검색
			{
				printf("거주지 번호를 고르세요: 0.서울 1.경기 2.강원 3.충청 4.경상 5.전라\n"); scanf("%d", &locN); // 검색할 지역 번호 입력
				if (locN != 0 && locN != 1 && locN != 2 && locN != 3 && locN != 4 && locN != 5) { printf("거주지를 잘못 입력했습니다!! 다시 시도해주십시오 \n"); getchar(); continue; } // 잘못된 번호 입력할 경우 처음으로 돌아감
					getLoc(&H, &T, &loc,locN); // getLoc 함수 호출로 검색한 지역의 확진자 출력 
			}
			getchar(); // 명령 입력시 \n값 없애줌
			printf("\n"); //다음줄로 넘어감
		}

		//출력
		else if (oper == 'W') // W 명령을 입력한 경우
		{
			getchar(); // 명령 입력시 \n값 없애줌
			printWarning(&H, &T, &sex, &loc, &death); // printWarning함수 호출로 전체 리스트의 출력 , 통계치 출력, 위험한 지역 출력 
			
		}

		//삭제
		else if (oper == 'D') // D 명령을 입력한 경우
		{
			
			delete(&H, &T); // delete 함수 호출로 원하는 확진자 삭제
			getchar(); // 명령 입력시 \n값 없애줌
		}
		
		printf("\n\n"); // 줄바꿈
	}

	return 0; // 반환
}

