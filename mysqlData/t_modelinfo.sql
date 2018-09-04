/*
Navicat MySQL Data Transfer

Source Server         : ConnectMySql
Source Server Version : 50717
Source Host           : localhost:3306
Source Database       : osg

Target Server Type    : MYSQL
Target Server Version : 50717
File Encoding         : 65001

Date: 2018-05-23 17:58:52
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_modelinfoa`
-- ----------------------------
DROP TABLE IF EXISTS `t_modelinfoa`;
CREATE TABLE `t_modelinfoa` (
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
-- Records of t_modelinfoa
-- ----------------------------
INSERT INTO `t_modelinfoa` VALUES ('1', '主要部件', '0', '0', '0', '1', '2', null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO `t_modelinfoa` VALUES ('2', '汽轮机', null, null, null, '1', '0', null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO `t_modelinfoa` VALUES ('3', '附加部件', '0', '0', '0', '1', '2', null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO `t_modelinfoa` VALUES ('4', '箱板1', '50', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\XB_model1.OSG', null, null, null, null, null, null, null, null, null, '-1');
INSERT INTO `t_modelinfoa` VALUES ('5', 'asm2', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\asm2.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('6', '导管1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\DGmodel1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('7', '曲支座1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\QZZ_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('8', '上盖1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\SG1_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('9', '曲支不带头', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\QZBDT.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('10', '汽封1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\QF_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('11', '上盖2', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\SG2_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('12', '管del1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\Gdel1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('13', '小箱板', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\XXB.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('14', '小上盖1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\XSG1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('15', '轴承出气端外环1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\ZCCQDWH_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('16', '中间轴承外圈', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\ZJZCWQ.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('17', '轴承出气端内环', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\ZCCQDNH.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('18', '进气导管1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\JQDG1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('19', '进气联轴器1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\JQLZQ1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('20', '联轴', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\LZ_model1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('21', 'TUBINE_step', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\TUBINE_step.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('22', '进气端轴承外环1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\JQDZCWH1.OSG', null, null, null, null, null, null, null, null, null, null);
INSERT INTO `t_modelinfoa` VALUES ('23', '进气端轴承内环1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\osgFiles\\JQDZCNH1.OSG', null, null, null, null, null, null, null, null, null, null);
