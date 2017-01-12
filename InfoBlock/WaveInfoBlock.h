#pragma once

#include <InfoBlock/IInfoBlock.h>
#include <InfoBlock/ImageAndNumber.h>

class CWaveInfoBlock : public IInfoBlock
{
    Q_OBJECT
public:
    CWaveInfoBlock(CGame *game);

    const int InternalOffsetX = 15;
    const int InternalOffsetY = 15;

    std::shared_ptr<CImageAndNumber> waveCounter;
    std::shared_ptr<CImageAndNumber> enemyCounter;

    virtual void scale() override;
    virtual void remove() override;
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;

    void onEnemyNumChanged(int enemyNum);
    void onCurWaveChanged(int newCurWave);
    
    int getTotalWaveNum() const;
    void setTotalWaveNum(int value);
    
private:
    int totalWaveNum;
};

