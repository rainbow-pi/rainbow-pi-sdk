#ifndef _ADAS_INTERFACE_H_
#define _ADAS_INTERFACE_H_

#include "Adas.h"

typedef struct
{
	  ADASOUT *adasOut;
	  int subWidth;
	  int subHeight;
}ADASOUT_IF;

#define getAdasOutDataLength(adasOut_if) \
    (  sizeof(unsigned char) /* adasOut->lane.isDisp */ \
     + sizeof(unsigned char) /* adasOut->lane.ltWarn */ \
     + sizeof(unsigned char) /* adasOut->lane.rtWarn */ \
     + sizeof(PointC) * 2 /* adasOut->lane.ltIdxs */ \
     + sizeof(PointC) * 2 /* adasOut->lane.rtIdxs */ \
     + sizeof(int) /* adasOut->lane.colorPointsNum */ \
     + sizeof(unsigned char) /* adasOut->lane.dnColor */ \
     + sizeof(unsigned short) * adasOut_if->adasOut->lane.colorPointsNum /* adasOut->lane.rows */ \
     + sizeof(unsigned short) * adasOut_if->adasOut->lane.colorPointsNum /* adasOut->lane.rtCols */ \
     + sizeof(unsigned short) * adasOut_if->adasOut->lane.colorPointsNum /* adasOut->lane.mdCols */ \
     + sizeof(unsigned short) * adasOut_if->adasOut->lane.colorPointsNum /* adasOut->lane.ltCols */ \
     + sizeof(int) /* adasOut->cars.Num */ \
     + sizeof(CAR) * adasOut_if->adasOut->cars.Num /* adasOut->cars.carP */ \
     + sizeof(int) /* adasOut->plates.Num */ \
     + sizeof(PLATE) * adasOut_if->adasOut->plates.Num /* adasOut->plates.plateP */ \
     + sizeof(int) /* adasOut->score */ \
     + sizeof(int) /* subWidth */ \
     + sizeof(int) /* subHeight */)
#endif

