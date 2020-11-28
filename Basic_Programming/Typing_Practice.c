#include <stdio.h>
#include <stdlib.h>     // rand, srand 함수 
#include <time.h>       // time 함수, clock 함수
#include <string.h>		// strcmp 함수
#include <termio.h>		// getch, getche 함수
#include <unistd.h>		// sleep 함수

int getch();
void first();
void second();
void third();
void fourth();

int main()
{
	char menucount = 0;

	while (menucount != '5')
	{
		// 메뉴 시작
		system("clear");

		printf(">> 영문 타자 연습 프로그램 <<\n");
		printf("1. 자리 연습		2. 낱말 연습\n");
		printf("3. 짧은 글 연습		4. 긴 글 연습\n");
		printf("5. 프로그램 종료\n\n");
		printf("번호를 선택하세요: ");

		menucount = getch();
		printf("%c\n", menucount);

		switch (menucount)
		{
		case '1':
			first();
			break;
		case '2':
			second();
			break;
		case '3':
			third();
			break;
		case '4':
			fourth();
			break;
		case '5':
			system("clear");
			break;
		default:	// 1~5가 아닌 문자를 입력 받으면 다시 입력 받음
			continue;
		}
	}

	return 0;
}

int getch()
{
	int ch;

	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;

	buf.c_lflag &= ~(ICANON | ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;

	tcsetattr(0, TCSAFLUSH, &buf);

	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);

	return ch;
}

void first()	// 자리 연습
{
	int trial = 0;      // 시도수
	int typo = 0;		// 오타수
	int progress = 0;	// 진행도
	int accuracy = 0;	// 정확도
	char answer = 65;	// trial = 0, 최초시도시 문제 출력 될 때 if문의 조건을 맞추기 위해
	int i = 0;
	srand(time(NULL));

	char random[52];				// 문제 배열 생성
	for (int j = 0; j < 26; j++)	// A~Z
		random[j] = 65 + j;
	for (int j = 26; j < 52; j++)	// a~z
		random[j] = 71 + j;

	while (trial < 20)	// 20번 입력 받음
	{
		system("clear");

		printf(" >> 영문 타자 연습프로그램 : 자리 연습 <<\n");
		printf("진행도 : %3d%%    오타수 : %2d    정확도 : %3d%%\n", progress, typo, accuracy);

		if (answer == random[i])	// 문제를 맞춰야만 다음 문제로 넘어감(최초에는 바로 i값 생성)
			i = rand() % 52;

		printf("\n%c\n", random[i]);
		answer = getch();
		printf("%c\n", answer);

		// esc 누르면 메뉴로 이동
		if (answer == 27)
			return;

		if ((random[i] != answer) && (trial < 20))	// 틀렸을 시 오타수, 시도수 증가
		{
			printf("\r");
			typo++;
		}
		trial++;

		progress = 5 * (trial - typo);
		accuracy = 100 * (trial - typo) / trial;
		
		if (trial > 19)
			break;
	}
	
	system("clear");
	// 통계 출력
	printf(" >> 영문 타자 연습프로그램 : 자리 연습 <<\n");
	printf("진행도 : %3d%%    오타수 : %2d    정확도 : %3d%%\n", progress, typo, accuracy);
	// 프로그램 잠시 멈춘 뒤 엔터를 입력 받으면 종료
	sleep(2);
	while (1)	// 엔터를 입력 받을 때까지 무한루프
	{
		answer = getch();
		if (answer == 10)
			break;
	}

	return;
}

void second()
{
	int trial = 0; 	     // 시도수
	int progress = 0;    // 진행도
	int accuracy = 0;	 // 정확도
	int typo = 0;		 // 오타수
	char answer[20];
	srand(time(NULL));

	char words100[100][20] = {
		"alice", "academy", "ambulance", "array", "away", "always", "adhd", "apple", "acquire", "affair",
		"banana", "basic", "balance", "behind", "back", "bill", "be", "believe", "below", "bang",
		"clear", "can", "cow", "call", "claim", "char", "change", "character", "cook", "cap",
		"dragon", "danger", "damage", "delivery", "deal", "do", "define", "decide", "degree", "declare",
		"electric", "earth", "emergency", "eraser", "effect", "effort", "each", "early", "employee", "efficient",
		"find", "flare", "fall", "fill", "follow", "funk", "feature", "factor", "feel", "face",
		"glue", "go", "general", "get", "gather", "gentle", "garage", "gear", "generation", "genius",
		"hi", "hello", "how", "hangout", "halo", "have", "happen", "head", "handle", "happy",
		"identify", "implement", "indicate", "imagine", "illusion", "individual", "impact", "imply", "increase", "influence",
		"join", "judge", "jealous", "justice", "junior", "joint", "journal", "just", "jam", "job" };

	// 100개의 단어를 a~j까지 각각 10개씩 배열하였음.
	// [100][20]이 의미하는 바 : 100개의 문자열, 한 문자열 당 20칸

	while (trial < 20)
	{
		system("clear");

		printf(">> 영문 타자 연습 : 낱말 연습 <<\n");
		printf("진행도 : %3d%%    오타수 : %2d    정확도 : %3d%%\n\n", progress, typo, accuracy);

		int word_i = rand() % 100;
		printf("%s\n", words100[word_i]);
		scanf("%s", answer);          // answer 배열이니 & 없음

		if (!strcmp(words100[word_i], answer) && trial < 20)
		{   // 단어 맞는 경우
			progress++;
			trial++;
			accuracy++;
		}
		else if (!strcmp(answer, "###")) // ### 입력하면 메뉴로 복귀
			return;
		else if (trial >= 20)
			break;
		else if (answer[trial] == 0)
		{
			progress++;
			typo++;
			trial++;
		}
		else		// 단어 틀린 경우
		{
			progress++;
			typo++;
			trial++;
		}

		progress = 5 * (trial);  // 진행도
		accuracy = 100 * (trial - typo) / trial;  // 정확도
	}	// while문 종료

	system("clear");	// 21이 되면서 enter입력 후(진행도 100%이 됐을 때)바로 메뉴로 돌아가는거 방지	
	getch();
	// 통계 출력
	printf(">> 영문 타자 연습 : 낱말 연습 <<\n");
	printf("진행도 : %3d%%    오타수 : %2d    정확도 : %3d%%\n", progress, typo, accuracy);
	// 프로그램 잠시 멈춘 뒤 엔터를 입력 받으면 종료
	sleep(2);
	while (1)	// 엔터를 입력 받을 때까지 무한루프
	{
		char answer = getch();
		if (answer == 10)
			break;
	}
	
	return;
}

void third()
{
	int accuracy = 0;		// 정확도
	int trial = 0;			// 입력한 문자 수
	int correct = 0;		// 맞은 문자 수
	unsigned int tspeed = 0;			// 타수
	int maxspeed = 0;		// 최고타수
	int progress = 0;		// 진행도
	int letter = 0;			// 몇번째 문자를 입력하고 있는지
	time_t start_time, end_time;
	double total_time = 0;
	srand(time(NULL));

	int random;
	char sentence[30][80] = {	// 제일 긴 문장 길이 57+'\0'=58
		"Seeing is believing",
		"You will never know until you try",
		"Let bygones be bygones",
		"Do not count the eggs before they hatch",
		"Life is venture or nothing",
		"She can do, he can do, why not me?",
		"Step by step goes a long way",
		"Rome was not built in a day",
		"Little by little does the trick",
		"To climb steep hills requires slow pace at first",
		"A rolling stone gathers no moss",
		"There is no royal road to learning",
		"Where there's a will, there's a way",
		"If you do not walk today, you will have to run tomorrow",
		"Early bird catches the worm",
		"A bad workman always blames his tools",
		"Put off for one day and ten days will pass",
		"The beginning is half of the whole",
		"Asking costs nothing",
		"Knowledge in youth is wisdom in age",
		"A gift in season is a double favor to the needy",
		"All fortune is to be conquered by bearing it",
		"Better is to bow than break",
		"Better the last smile than the first laughter",
		"Books are ships which pass through the vast seas of time",
		"By doubting we come at the truth",
		"Education is the best provision for old age",
		"Faith without deeds is useless",
		"Forgiveness is better than revenge",
		"Give me liberty, or give me death" };

	for (int count = 0; count < 5; count++)	// 5번 동안 반복함
	{
		random = rand() % 30;	// 30개의 글 중 랜덤으로 하나를 선택
		char input[80] = { 0 };	// 입력을 받을 배열.

		while (1)
		{
			system("clear");

			printf(">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<\n");
			printf("진행도 : %3d%%	현재타수 : %3u	최고타수 : %3d	정확도 : %3d%%\n\n", progress, tspeed, maxspeed, accuracy);

			printf("%s\n", sentence[random]);	// 짧은 글 한 줄 출력
			for (int i = 0; i < letter; i++)		// 내가 입력한 답안 출력
				printf("%c", input[i]);

			start_time = time(NULL);
			input[letter] = getch();		// 답안 입력, 시간 측정
			end_time = time(NULL);
			total_time += difftime(end_time, start_time);

			if (input[letter] == 27)				// esc 입력시 fourth 함수 종료. 메뉴로 복귀
				return;
			if (input[letter] == 10)				// 엔터 입력시 다음 문제 출력 
				break;
			if (input[letter] == 127)				// BS 입력, 한 칸 전으로 이동, 공백 출력 후 다시 전 칸에서 출력		
			{
				if (letter > 0)
				{
					input[letter - 1] = 0;
					letter -= 2;
					trial -= 2;
				}
				else if (letter == 0)				// 입력한 문자가 없을시 BS 입력해도 아무 변화 없음
					continue;
			}

			correct = 0;
			for (int i = 0; sentence[random][i] != 0; i++)
			{
				if (input[i] == sentence[random][i])	// 문제 배열의 처음부터 끝까지 답안 배열과 비교
					correct++;							// 문자 맞게 입력시 맞은 문자수 1 증가
			}

			letter++;	// 출력할 문자 자리수 1증가
			trial++;	// 입력한 문자 수 1증가
			if (trial == 0)		// 문자 하나 입력 후 백스페이스 입력하면 정확도 분모에 0 들어가는거 방지하려고 추가
			{
				accuracy = 0;
				tspeed = 0;
			}
			else
			{
				accuracy = 100 * correct / trial;			
				(int)(tspeed = 60 * correct / total_time);
				if ((int)tspeed - maxspeed > 0)		// 현재타수가 최고타수 보다 높으면 최고타수에 현재타수 할당
				{
					maxspeed = (int)tspeed;
				}
			}
		}	// while 문 종료
		progress += 20;				// 한 문장 끝날 때마다 진행도 20% 증가

		if (count < 4)				// 다음 문장 출력 전, 정확도와 현재 타수 초기화
		{							// 마지막 입력 종료시에는 정확도와 현재타수가 남아있어야함
			trial = 0;
			total_time = 0;
			letter = 0;
			accuracy = 0;
			tspeed = 0;
		}
	}
	
	system("clear");
	// 통계 출력
	printf(">> 영문 타자 연습 프로그램 : 짧은 글 연습 <<\n");
	printf("진행도 : %3d%%	현재타수 : %3u	최고타수 : %3d	정확도 : %3d%%\n\n", progress, tspeed, maxspeed, accuracy);
	// 잠시 정지 뒤 프로그램 종료
	sleep(2);
	while (1)
	{
		char answer = getch();		// 엔터 입력 받아야 종료
		if (answer == 10)
			break;
	}

	return;
}

void fourth()
{
	int accuracy = 0;				// 정확도
	int trial = 0;					// 입력한 문자 수
	int correct = 0;				// 맞은 개수
	unsigned int tspeed = 0;		// 타수
	int line = 0, letter = 0;		// 입력중인 줄, 문자
	time_t start_time, end_time;
	double total_time = 0;
	srand(time(NULL));

	int random;
	char lsent[4][10][100] = {
		{ "Pride and Prejudice",
		"It is a truth universally acknowledged, that a single man in possession",
		"of a good fortune, must be in want of a wife.",
		"However little known the feelings or views of such a man may be on his",
		"first entering a neighbourhood, this truth is so well fixed in the minds",
		"of the surrounding families, that he is considered the rightful property",
		"of someone or other of their daughters.",
		"\"My dear Mr. Bennet,\" said his lady to him one day, \"have you heard that",
		"Netherfield Park is let at last?\"",
		"Mr. Bennet replied that he had not." },
		{ "Moby-Dick",
		"Call me Ishmael. Some years ago-never mind how long precisely-having",
		"little or no money in my purse, and nothing particular to interest me on",
		"shore, I thought I would sail about a little and see the watery part of",
		"the world. It is a way I have of driving off the spleen and regulating",
		"the circulation. Whenever I find myself growing grim about the mouth;",
		"whenever it is a damp, drizzly November in my soul; whenever I find",
		"myself involuntarily pausing before coffin warehouses, and bringing up",
		"the rear of every funeral I meet; and especially whenever my hypos get",
		"such an upper hand of me, that it requires a strong moral principle to" },
		{ "Peter Pan",
		"All children, except one, grow up. They soon know that they will grow up,",
		"and the way Wendy knew was this. One day when she was two years old she",
		"was playing in a garden, and she plucked another flower and ran with it",
		"to her mother. I suppose she must have looked rather delightful, for Mrs.",
		"Darling put her hand to her heart and cried, \"Oh, why can't you remain like",
		"this forever!\" This was all that passed between them on the subject, but",
		"henceforth Wendy knew that she must grow up. You always know after you are",
		"two. Two is the beginning of the end. Of course they lived at 14 [their house",
		"number on their street], and until Wendy came her mother was the chief one." },
		{ "A Study In Scalet",
		"In the year 1878 I took my degree of Doctor of Medicine of the University",
		"of London, and proceeded to Netley to go through the course prescribed for",
		"surgeons in the army. Having completed my studies there, I was duly attached",
		"to the Fifth Northumberland Fusiliers as Assistant Surgeon. The regiment was",
		"stationed in India at the time, and before I could join it, the second Afghan",
		"war had broken out. On landing at Bombay, I learned that my corps had advanced",
		"through the passes, and was already deep in the enemy’s country. I followed,",
		"however, with many other officers who were in the same situation as myself,",
		"and succeeded in reaching Candahar in safety" } };

	random = rand() % 4;		// 4개의 글 중 랜덤으로 한 글 출력
	char input[10][100] = { 0 };	// 입력 받을 배열

	for (int page = 1; page < 3; page++) // 두 번 반복 (첫번째 페이지, 두번째 페이지)
	{
		while (1)
		{
			system("clear");

			printf(">> 영문 타자 연습 프로그램 : 긴 글 연습 <<\n");
			printf("정확도 : %3d%%	현재타수 : %u\n\n", accuracy, tspeed);

			if (page == 1)								// 첫번째 페이지 문제
			{
				for (int i = 0; i < 5; i++)
					printf("%s\n", lsent[random][i]);	// 문제 5줄 출력
				printf("\n");

				for (int i = 0; i < line; i++)			// 내가 입력한 답안 출력
				{
					printf("%s\n", input[i]);
				}
				for (int j = 0; j < letter; j++)
				{
					printf("%c", input[line][j]);
				}
			}
			else if (page == 2)							// 두번째 페이지 문제
			{
				for (int i = 5; i < 10; i++)
					printf("%s\n", lsent[random][i]);	// 문제 5줄 출력
				printf("\n");

				for (int i = 5; i < line; i++)
				{
					printf("%s\n", input[i]);
				}
				for (int j = 0; j < letter; j++)
				{
					printf("%c", input[line][j]);
				}
			}

			start_time = time(NULL);
			input[line][letter] = getch();			// 내 답안 입력, 시간 측정
			end_time = time(NULL);
			total_time += difftime(end_time, start_time);

			if (input[line][letter] == 27)				// esc 입력시 fourth 함수 종료. 메뉴로 복귀
				return;
			if (input[line][letter] == 127)				// BS 입력시 한칸 전으로 이동 공백 출력후 다시 전칸에서 출력		
			{
				if (letter > 1)
				{
					input[line][letter - 1] = 0;
					letter -= 2;
					trial -= 2;
				}
				else if (letter == 0)					// 입력한 문자가 없을시 BS 입력해도 아무 변화 없음
					continue;
			}

			if (lsent[random][line][letter] == 0)		// 한 줄 입력 끝나고 1. 엔터 2. 다음문자
			{
				if (input[line][letter] == 10)			// 1. 엔터 입력시 다음줄의 첫째자리 입력으로 이동
				{
					input[line][letter] = 0;
					letter = 0;
					line++;
					if (page == 1)
					{
						if (line == 5)	// 1번째 페이지 5줄 입력 끝났다면 다음 장으로
							break;
					}
					if (page == 2)		// 2번째 페이지 5줄 입력 끝났다면 종료
					{
						if (line == 10)
							break;
					}
					continue;
				}
				else									// 2. 다음 문자 입력시 다음줄의 첫째자리에 바로 할당
				{
					input[line + 1][0] = input[line][letter];
					input[line][letter] = 0;
					letter = 0;
					line++;
					if (page == 1)
					{
						if (line == 5)	// 1번째 페이지 5줄 입력 끝났다면 다음 장으로
							break;
					}
					if (page == 2)		// 2번째 페이지 5줄 입력 끝났다면 종료
					{
						if (line == 10)
							break;
					}
				}
			}

			if (input[line][letter] == 10)				// (입력 도중) 엔터 입력시 다음 줄로 이동 
			{
				while (lsent[random][line][letter] != 0)	// 입력을 건너뛴 모든 답안 자리에 0 할당, 오타 입력한 것으로 간주
				{
					input[line][letter] = 0;
					letter++;
					trial++;
				}
				letter--;				
				trial--;
			}

			if (input[line][letter] == 127)				// letter 1 일때, BS 입력		
			{
				if (letter == 1)
				{
					input[line][letter - 1] = 0;
					letter -= 2;
					trial -= 2;
				}
			}

			correct = 0;
			for (int i = 0; i <= line; i++)
			{
				for (int j = 0; lsent[random][i][j] != 0; j++)
				{
					if (input[i][j] == lsent[random][i][j])	// 문자 맞게 입력시
						correct++;
				}
			}

			letter++;
			trial++;
			if (trial == 0)		// 문자 하나 입력 후 백스페이스 입력 가능하게 하려고 추가함
			{
				accuracy = 0;
				tspeed = 0;
			}
			else
			{
				accuracy = 100 * correct / trial;
				tspeed = 60 * correct / total_time;
			}

			if ((lsent[random][line][letter] == 0) && (input[line][letter - 1] == 0))	// 입력 도중에 엔터 입력에 이어 받아서 실행되는 부분
			{
				letter = 0;
				line++;
				if (page == 1)
				{
					if (line == 5)	// 5줄 입력 완료시 다음 장으로
						break;
				}
				if (page == 2)
				{
					if (line == 10)
						break;
				}
			}
		}		// while 문 종료
	}			// for 문 종료
	
	system("clear");
	// 통계 출력
	printf(">> 영문 타자 연습 프로그램 : 긴 글 연습 <<\n");
	printf("정확도 : %3d%%	현재타수 : %u\n\n", accuracy, tspeed);
	// 입력 다 끝나고 잠시 정지 뒤 프로그램 종료
	sleep(2);
	while (2)
	{
		char answer = getch();
		if (answer == 10)
			break;
	}

	return;
}
