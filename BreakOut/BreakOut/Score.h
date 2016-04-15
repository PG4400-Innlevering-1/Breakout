#pragma once
class Score
{
public:
	Score();
	~Score();

	int getScore() const { return score; }

	void addScore();

	void resetScore();

private:
	int score;
};

