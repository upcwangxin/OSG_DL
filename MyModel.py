
import numpy as np
import pandas as pd
import pylightgbm as lgb
from sklearn import metrics
from sklearn.model_selection import train_test_split



### 读取数据
print("载入数据")
dataset1 = pd.read_csv('G:/3dOSG/osg/DL/data/7_train_data1.csv')
dataset2 = pd.read_csv('G:/3dOSG/osg/DL/data/7_train_data2.csv')
dataset3 = pd.read_csv('G:/3dOSG/osg/DL/data/7_train_data3.csv')
dataset4 = pd.read_csv('G:/3dOSG/osg/DL/data/7_train_data4.csv')
dataset5 = pd.read_csv('G:/3dOSG/osg/DL/data/7_train_data5.csv')

dataset1.drop_duplicates(inplace=True)
dataset2.drop_duplicates(inplace=True)
dataset3.drop_duplicates(inplace=True)
dataset4.drop_duplicates(inplace=True)
dataset5.drop_duplicates(inplace=True)

trains = pd.concat([dataset1, dataset2], axis=0)
trains = pd.concat([trains, dataset3], axis=0)
trains = pd.concat([trains, dataset4], axis=0)

online_test = dataset5

### 特征选择
# 4-15
# 删除贡献度为0的特征
"""
delete_columns = ['item_category2_click_count_today',
            'gender_click_count_today',
            'item_city_click_count_today',
            'user_hour_buy_count',
            'user_shop_buy_count',
            'item_shop_click_count_today',
            'item_brand_click_count_today',
            'user_item_buy_count',
            'context_day_gap']

trains.drop(delete_columns,axis = 1,inplace = True)
online_test.drop(delete_columns,axis = 1,inplace = True)
"""

# 2018-4-15
# 删除贡献度<=10的特征
delete_columns = ['brand_buy_count',
                  'user_buy_count',
                  'gender_category2_click_count_today',
                  'gender_city_click_count_today',
                  'item_shop_buy_count',
                  'user_category2_click_count_today',
                  'item_shop_click_count',
                  'user_page_buy_count',
                  'item_city_click_count',
                  'city_page_click_count_today',
                  'occupation_category2_click_count_today',
                  'item_click_count_today',
                  'occupation_click_count_today',
                  'occupation_buy_count',
                  'brand_page_click_count_today',
                  'occupation_click_count',
                  'is_second_cat',
                  'user_brand_buy_count',
                  'gender_click_count']

trains.drop(delete_columns, axis=1, inplace=True)
online_test.drop(delete_columns, axis=1, inplace=True)

# PCA
"""
from sklearn.decomposition import PCA
train_pca = PCA(n_components ='mle')
train_pca.fit(trains)                      # 训练：n_compoents='mle'表示自动确定需要保留的特征数
train_pca.transform(trains)                # 降维：
train_pca.inverse_transform(trains)        # 反转：
print(train_pca.explained_variance_ratio_) # 属性：特征的方差贡献率
"""
# 数据集信息
print("训练集基本信息")
print(trains.info())
print("测试集基本信息")
print(online_test.info())

### 数据拆分
print("数据拆分")
train_xy, offline_test = train_test_split(trains, test_size=0.2, random_state=21)
train, val = train_test_split(train_xy, test_size=0.2, random_state=21)

print("训练集")
y = train.is_trade  # 训练集标签
X = train.drop(['instance_id', 'is_trade'], axis=1)  # 训练集特征矩阵

print("验证集")
val_y = val.is_trade  # 验证集标签
val_X = val.drop(['instance_id', 'is_trade'], axis=1)  # 验证集特征矩阵

print("测试集")
offline_test_X = offline_test.drop(['instance_id', 'is_trade'], axis=1)  # 线下测试特征矩阵
online_test_X = online_test.drop(['instance_id'], axis=1)  # 线上测试特征矩阵

### 数据转换
lgb_train = lgb.Dataset(X, y, free_raw_data=False)
lgb_eval = lgb.Dataset(val_X, val_y, reference=lgb_train, free_raw_data=False)

### 开始训练
print('设置参数')
params = {
    'boosting_type': 'gbdt',
    'boosting': 'dart',
    'objective': 'binary',
    'metric': 'binary_logloss',

    'learning_rate': 0.01,
    'num_leaves': 31,
    'max_depth': 3,

    'max_bin': 10,
    'min_data_in_leaf': 8,

    'feature_fraction': 0.6,
    'bagging_fraction': 1,
    'bagging_freq': 0,

    'lambda_l1': 0,
    'lambda_l2': 0,
    'min_split_gain': 0
}

print("开始训练")
gbm = lgb.train(params,  # 参数字典
                lgb_train,  # 训练集
                num_boost_round=2000,  # 迭代次数
                valid_sets=lgb_eval,  # 验证集
                early_stopping_rounds=30)  # 早停系数
### 线下预测
print("线下预测")
preds_offline = gbm.predict(offline_test_X, num_iteration=gbm.best_iteration)  # 输出概率
offline = offline_test[['instance_id', 'is_trade']]
offline['preds'] = preds_offline
offline.is_trade = offline['is_trade'].astype(np.float64)
print('log_loss', metrics.log_loss(offline.is_trade, offline.preds))

### 线上预测
print("线上预测")
preds_online = gbm.predict(online_test_X, num_iteration=gbm.best_iteration)  # 输出概率
online = online_test[['instance_id']]
online['preds'] = preds_online
online.rename(columns={'preds': 'predicted_score'}, inplace=True)
online.to_csv("G:/3dOSG/osg/DL/data/20180415.txt", index=None, sep=' ')

### 保存模型
from sklearn.externals import joblib

joblib.dump(gbm, 'gbm.pkl')

### 特征选择
df = pd.DataFrame(X.columns.tolist(), columns=['feature'])
df['importance'] = list(gbm.feature_importance())
df = df.sort_values(by='importance', ascending=False)
df.to_csv("G:/3dOSG/osg/DL/data/feature_score_201804015.csv", index=None, encoding='gbk')
