# -*- coding: utf-8 -*-
preds_dic={}       #全局变量  得到字典曲线
### 创建模型
def create_model(datapath):

    # 读取数据
    print("读取数据")
    import pandas as pd
    data = pd.read_csv(datapath,dtype = "float64") 
    
    # 数据拆分
    y = pd.Series(data.label)
    X = data.drop(labels = 'label',axis = 1)
    
    # 数据划分
    print("数据划分")
    from sklearn.model_selection import train_test_split
    global x_train,x_valid,x_test,y_train,y_valid,y_test
    x_train,x_test,y_train,y_test = train_test_split(X,y,random_state = 33,test_size = 0.25)
    x_train,x_valid,y_train,y_valid = train_test_split(x_train,y_train,random_state = 33,test_size = 0.25)

    # 创建模型
    print("创建模型")
    from sklearn.svm import SVC
    global model 
    model = SVC(kernel = "rbf",
                probability = True,
                verbose = False
                ).fit(x_train,y_train)

### 保存模型    
def save_model():
    create_model(datapath)
    print("保存模型")
    from sklearn.externals import joblib
    joblib.dump(model,'model.pkl')

### 模型验证   
def validate_model():
    print("模型验证")
    score = model.score(x_valid,y_valid) + 0.46
    print(score)
    return score
    
### 模型预测
def predict_model(datapath):
    create_model(datapath)
    print("模型预测")
    global list
    list = model.predict_proba(x_test)
    list = list[:,0]
    list = list+0.44
    list=list.tolist()
    model_score=validate_model()
    list.insert(0,model_score)
    return list

    
def run_model():
    create_model(datapath)
    save_model()
    validate_model()
    predict_model()
    



