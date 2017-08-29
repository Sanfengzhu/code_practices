class Transaction {

	bool PriamryPrewrite() {
			
	}

	bool PrimaryPrewriteCallback() {
		for() {
			SetCallback(PrewriteCallback);
			Prewrite();
		}
	}

	bool Prewrite() {
		
	}

	bool PrewriteCallback() {
		// get prewrite result 
		// 统计结果
		// 调用InternalCommit
		// 
		// async call primary commit 
		SetCallback(InternalCommitCallback);
		InternalCommit();
	}

	bool InternalCommit() {
		
	}
	
	bool InternalCommitCallback() {
		return result;
		push_back(OtherThread);
	}

	bool Commit() {
		// async call all perwrite
		SetCallback(PrimaryPrewriteCallback);
		PrimaryPrewrite();
				
	}
}
