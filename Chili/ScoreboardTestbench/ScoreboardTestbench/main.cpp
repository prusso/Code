#include <stdio.h>
#include <stdlib.h>

class Score
{
public:
	Score( int score, const char* time )
	{
		this->score = score;
		this->time = (char*)malloc(strlen(time) + 1);
		strcopy(this->time, time);
		nextScore = NULL;
	}
	Score( FILE* file );
	Serialize( FILE* file );
	bool Insert( Score* inScore )
	{
		if (inScore->score <= score)
		{
			if (nextScore->Insert(inScore) == true)
			{
				inScore->nextScore = nextScore;
				nextScore = inScore;
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true; //true means this is the correct position in the list
		}
	}
	Score* Next();
	~Score()
	{
		free(time);
	}
private:
	int score;
	char* time;
	Score* nextScore;
};
public:
	ScoreBoard();
	~ScoreBoard();
	void AddScore(int score, const char* time);
	void Test()
	{

	}
private:
	Score* firstScore;
};

void main()
{
	
}