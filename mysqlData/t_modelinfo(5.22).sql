/*
Navicat MySQL Data Transfer

Source Server         : ConnectMySql
Source Server Version : 50717
Source Host           : localhost:3306
Source Database       : osg

Target Server Type    : MYSQL
Target Server Version : 50717
File Encoding         : 65001

Date: 2018-05-22 12:42:16
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_modelinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_modelinfo`;
CREATE TABLE `t_modelinfo` (
  `iModelID` int(4) NOT NULL,
  `iModelName` varchar(50) DEFAULT NULL,
  `dCoordX` double(20,0) DEFAULT NULL,
  `dCoordY` double(20,0) DEFAULT NULL,
  `dCoordZ` double(20,0) DEFAULT NULL,
  `iNode` int(2) DEFAULT NULL,
  `iParent` int(4) DEFAULT NULL,
  `cPath` varchar(50) DEFAULT NULL,
  `dCoordX_New` double(20,0) DEFAULT NULL,
  `dCoordY_New` double(20,0) DEFAULT NULL,
  `dCoordZ_New` double(20,0) DEFAULT NULL,
  `colorOld_R` double(20,0) DEFAULT NULL,
  `colorOld_G` double(20,0) DEFAULT NULL,
  `colorOld_B` double(20,0) DEFAULT NULL,
  `colorNew_R` double(20,0) DEFAULT NULL,
  `colorNew_G` double(20,0) DEFAULT NULL,
  `colorNew_B` double(20,0) DEFAULT NULL,
  `level` int(8) DEFAULT NULL,
  PRIMARY KEY (`iModelID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_modelinfo
-- ----------------------------
INSERT INTO `t_modelinfo` VALUES ('1', '主要部件', '0', '0', '0', '1', '2', null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO `t_modelinfo` VALUES ('2', '汽轮机', null, null, null, '1', '0', null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO `t_modelinfo` VALUES ('3', '附加部件', '0', '0', '0', '1', '2', null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO `t_modelinfo` VALUES ('4', '箱板1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\XB_model1.OSG', null, null, null, null, null, null, null, null, null, '-1');
INSERT INTO `t_modelinfo` VALUES ('5', 'asm2', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\asm2.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('6', '导管1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\DGmodel1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('7', '曲支座1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\QZZ_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('8', '上盖1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\SG1_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('9', '曲支不带头', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\QZBDT.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('10', '汽封1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\QF_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('11', '上盖2', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\SG2_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('12', '管del1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\Gdel1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('13', '小箱板', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\XXB.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('14', '小上盖1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\XSG1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('15', '轴承出气端外环1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\ZCCQDWH_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('16', '中间轴承外圈', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\ZJZCWQ.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('17', '轴承出气端内环', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\ZCCQDNH.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('18', '进气导管1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\JQDG1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('19', '进气联轴器1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\JQLZQ1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('20', '进气端轴承外环1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\JQDZCWH1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('21', '进气端轴承内环1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\JQDZCNH1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('29', '联轴1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\LZ_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfo` VALUES ('30', 'TUBINESTEP', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\TUBINE_STEP.OSG', null, null, null, null, null, null, null, null, null, null);
