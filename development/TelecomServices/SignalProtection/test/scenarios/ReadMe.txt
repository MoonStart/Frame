

   ///////////////////////////////////////////////////////////////////////////////////
   /																				 /
   /								Read Me !!!										 /
   /																				 /
   ///////////////////////////////////////////////////////////////////////////////////

	About script for clsr and 1+1 debugging


	The command:

		#	

			Inserts a rem line that is ignored by the parser

		Check <side> <request> <destination> <source> <short|long path> <status>

			Checks if the k1k2 signal corresponds to the signal specified in the command

			Special note: An RDI_L status will not cause a failure of the command,
			              it will only sends a warning if the two status (real and predicted)
						  aren't the same.

			<side> :       the side of node EAST or WEST (west = left and east = right)
			<request> :    the request of the signal LP_S, FS_S, FS_R, SF_S, SF_R, SD_P, SD_S,
			               SD_R, MS_S, MS_R, WTR, EXER_S, EXER_R, RR_S, RR_R, NR.
			<destination>: to which node the message is destinated.
			<source>:      from which node the message come from.
			<short|long path>: if the message is a short path or long path. (SHORT, LONG, S , L)
			<status>:      status of the signal IDLE, BR, BR&SW, ET, RDI_L, AIS_L

		CheckCross <side> <status>

			TO DO

		CheckFsm <side> <fsm state>

			Check if the state of signal protection fsm corresponds to the state specified in the command


		Command <side> <command name>

		Failure <facility> <side> <defect name> <defect switch>

		Map <node ID> <node ID> ... <node ID>

		Print <string message>

		Protection <1+1|CLSR>

		Ring <east node ID> <west node ID> <y|n pass through>

		Run <file name>

		Send <facility> <side> <request> <destination> <source> <short|long path> <status>

		SetTimeOut <clean timeout> <dirty timeout> <exercice timeout>

		Wait <side> <request> <min timeout> <max time out>
