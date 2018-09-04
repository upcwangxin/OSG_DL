
### 仿真数据
def data_analysis(dataPath):
    ### 导入模块
    import numpy as np
    import pandas as pd
    import random 
    
    ### 载入数据
    print("载入数据")
    data = pd.read_csv(dataPath,header = None,dtype = "float64",sep = '\t')
    print(data.head(10))
    
    ### 仿真数据
    # 标签
    print("添加标签")
    label =np.zeros(data.shape[0])
    for i in data.index:
        label[i]= random.randint(0,1)
    
    data.insert(0,'label',label)
    
    # 故障原因1
    print("添加原因1")
    reason1 =np.zeros(data.shape[0])
    for i in data.index:
        reason1[i]= random.random()
    
    data.insert(1,'reason1',reason1)
    
    # 故障原因2
    print("添加原因2")
    reason2 =np.zeros(data.shape[0])
    for i in data.index:
        reason2[i]= random.random()
    
    data.insert(2,'reason2',reason2)
    
    # 故障原因3
    print("添加原因3")
    reason3 =np.zeros(data.shape[0])
    for i in data.index:
        reason3[i]= random.random()
    
    data.insert(3,'reason',reason3)
    
    ### 数据探索
    print(data.info())
    print(data.head())
    print(np.any(data.isnull()==True))
    
    """
    ### 特征选择--方差选择法
    from sklearn.feature_selection import VarianceThreshold
    vt = VarianceThreshold(threshold = 1)
    data = vt.fit_transform(data)
    """
    # 保存数据集
    data.to_csv('turbine_data_analysis.csv',index=None,encoding='gbk')
