// //Copyright(c) Tellabs Transport Group. All rights reserved.

#ifndef _CFG_HWREFRESHMESH_
#define _CFG_HWREFRESHMESH_

#include "CFG_HwRefreshAction.h"
#include "CFG_Definitions.h"
#include <TsPii/TSPII_Region.h>
/*
// Forward declaration of class.
//class CFG_Region;
class TSPII_SsmIf;

class CFG_Mesh;

//This action is invoked periodically in order to update 
//'MESH layer' hardware registers 
//with current 'MESH' configuration.
class CFG_HwRefreshMesh 
: public CFG_HwRefreshAction
{
public:
	//Constructor
	CFG_HwRefreshMesh(CFG_AppIf& theCfgIf,
                      TSPII_SsmRegion& theSsmPiiRegion);

	//Virtual destructor
	virtual ~CFG_HwRefreshMesh();

	//This method refreshes all hardware related to MESH Layer.
	//It reads the current value of each MESH layer parameter and
    //invokes the corresponding PII interface. This action is normally 
    // invoked upon a change of the region it handles.
    virtual FC_Object* Process(unsigned theRunReason,
                                     FC_Object* theInvokerObj,
                                     FC_Object* theParam= NULL);

private:

    TSPII_SsmRegion& mySsmPiiRegion;

};
*/
#endif /* _CFG_HWREFRESHMESH_ */
