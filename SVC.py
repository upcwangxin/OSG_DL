preds_dic={}       #全局变量  得到字典曲线
def create_model():
    ### 生成数据
    from sklearn.datasets import make_classification
    X, y = make_classification(n_samples=10000,            # 样本个数
                                   n_features=25,          # 特征个数
                                   n_informative=3,        # 有效特征个数
                                   n_redundant=2,          # 冗余特征个数（有效特征的随机组合）
                                   n_repeated=0,           # 重复特征个数（有效特征和冗余特征的随机组合）
                                   n_classes=8,            # 样本类别
                                   n_clusters_per_class=1, # 簇的个数
                                   random_state=0)
    print("原始特征维度",X.shape)
        
    ### 数据划分
    from sklearn.model_selection import train_test_split
    global x_a_train,x_a_test,y_a_train,y_a_test
    x_a_train,x_a_test,y_a_train,y_a_test = train_test_split(X,y,random_state = 33,test_size = 0.25)
    
    # 创建svc模型
    print("创建模型")
    from sklearn.svm import SVC
    global model
    model = SVC(kernel = "linear").fit(x_a_train,y_a_train)
    print(model.score(x_a_test,y_a_test))
    
    # 保存模型
    print("保存模型")
    from sklearn.externals import joblib
    joblib.dump(model,'xgb.pkl')

    # 调用定时打印函数
    timming_prediction()
    
def timming_prediction():
    # 定时预测
    print ("定时预测")
    #from apscheduler.schedulers.blocking import BlockingScheduler          #阻塞性任务分配  不适用
    from apscheduler.schedulers.background import BackgroundScheduler     #非阻塞型进程  能退出job
    from apscheduler.triggers.interval import IntervalTrigger
    import datetime
    import time
    from apscheduler.schedulers.tornado import TornadoScheduler
    import tornado.ioloop
    sched = BackgroundScheduler()
    # sched.add_job(job_ , 'cron', second='*/5')
    #  添加任务
    # 使用IntervalTrigger触发器指定时间运行
    trigger = IntervalTrigger(seconds=5,
                              start_date=datetime.datetime.now() ,
                              end_date=datetime.datetime.now() + datetime.timedelta(seconds=10))
    sched.add_job(job_,trigger)
    sched.start()
    #print('Press Ctrl+{0} to exit'.format('Break' if os.name == 'nt' else 'C'))
    count = 0
    try:
     while True:
        time.sleep(2)  # 其他任务是独立的线程执行
        count = count + 1
        if count == 3:
           return 'break'
    except (KeyboardInterrupt, SystemExit):
        sched.shutdown()
        print('Exit The Job!')
    finally:
        sched.shutdown()
        print('Exit The Job!')
# 定时预测函数的附属函数    
def job_():
    # 当前时间
    import time
    t1=time.localtime(time.time())
    t=time.strftime('%Y-%m-%d %H:%M:%S', t1)
    print(t)
    # 预测概率值
    #preds= model.predict(x_a_test)
    preds = model.score(x_a_test,y_a_test)
    print(preds)
    preds_dic[t]=preds


def get_result():   
    create_model()
    print(preds_dic)
    for v in preds_dic.values():
        print(v)
        break
    return v


#if __name__ == "__main__":
#    get_result()



