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
    std::shared_ptr<CImageAndNumber> currentWave;

    virtual void scale() override;
    virtual void remove() override;
    virtual void draw() override;
    virtual void hide() override;
    virtual void show() override;

public slots:
    void onCurWaveChanged(int newCurWave);
    void onCashChanged(int newCash);
};

