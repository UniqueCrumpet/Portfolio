#pragma once
#include "SFML/Graphics.hpp"

class SFML_SpriteAnimation
{
public:
	SFML_SpriteAnimation();
	~SFML_SpriteAnimation();

	//Member function to store the memory address of the texture to use
	void							setSpriteSheet(sf::Texture*	spriteTexture);

	//Member function to add a frame(Rectangle and centre)
	void							addFrame(sf::IntRect textureRect, sf::Vector2f centre);

	//Member function that return current frame information(Rectangle and Centre)
	bool							getCurrentFrame(sf::IntRect* rect, sf::Vector2f* centre);

	//Member fucntion to set delay between showing consecutive frames
	void							setFrameTime(float timeperFrame);

	//Member function that returns the delay between showing showing consecutive frames
	float							getTimePerFrame();

	//Member function that returns the address of the texture used
	sf::Texture*					getSpriteSheet();

	//Member function that returns the number of frames in the animation
	int								getNumberOfFrames();

	void							getTextureInfo(int newFrame, sf::IntRect* rect, sf::Vector2f* centre);

	//Member to set and get loop flags
	void							setLoop(bool loop);
	bool							isLooped() const;

	//Member functions to set and get interruptible flag
	void							setCanbeInterrupted(bool trueorfalse);
	bool							canbeInterrupted() const;

	//Member functions to increment and get frame number, and reset animation
	void							incrementFrameNumber();
	int								getCurrentFrameNumber();
	void							resetCurrentAnimation();

	//Member function to check if the animation is completed. This will never be true if the animation is looping
	bool							isCompleted();

	float							setFrameTime();

private:
	//Frames information(Rectangle and Centre)
	std::vector<sf::IntRect>		m_frameRectangleList;
	std::vector<sf::Vector2f>		m_frameCentreList;

	//Pointer to the texture object
	sf::Texture*					m_spriteSheet;

	//Current frame number and time delay
	int								m_currentFrameNumber;
	float							m_timeperFrame;

	//Animation controls
	bool							m_isLoop;
	bool							m_canBeInterrupted;



};

