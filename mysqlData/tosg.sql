/*
Navicat MySQL Data Transfer

Source Server         : ConnectMySql
Source Server Version : 50717
Source Host           : localhost:3306
Source Database       : osg

Target Server Type    : MYSQL
Target Server Version : 50717
File Encoding         : 65001

Date: 2018-05-20 15:16:48
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_modelattribute`
-- ----------------------------
DROP TABLE IF EXISTS `t_modelattribute`;
CREATE TABLE `t_modelattribute` (
  `attributeName` varchar(40) NOT NULL,
  `attributeValue` double(20,0) DEFAULT NULL,
  `attributeRemarks` varchar(100) DEFAULT NULL,
  `attributeId` int(2) NOT NULL,
  PRIMARY KEY (`attributeId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_modelattribute
-- ----------------------------
INSERT INTO `t_modelattribute` VALUES ('拆分速度', '3', null, '1');
INSERT INTO `t_modelattribute` VALUES ('重构速度', '3', null, '2');
INSERT INTO `t_modelattribute` VALUES ('温度坐标值刷新间隔', '2', null, '3');
INSERT INTO `t_modelattribute` VALUES ('温度坐标移动速度', '20', null, '4');
INSERT INTO `t_modelattribute` VALUES ('转速坐标刷新间隔', '1', null, '5');
INSERT INTO `t_modelattribute` VALUES ('转速坐标移动速度', '60', null, '6');
INSERT INTO `t_modelattribute` VALUES ('震动坐标刷新间隔', '1', null, '7');
INSERT INTO `t_modelattribute` VALUES ('震动坐标移动速度', '60', null, '8');
INSERT INTO `t_modelattribute` VALUES ('压力表盘刷新间隔', '0', null, '9');

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
INSERT INTO `t_modelinfo` VALUES ('1', '枝干一', '0', '0', '0', '1', '2', null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO `t_modelinfo` VALUES ('2', '根', null, null, null, '1', '0', null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO `t_modelinfo` VALUES ('3', '枝干二', null, null, null, '1', '2', null, null, null, null, null, null, null, null, null, null, '0');
INSERT INTO `t_modelinfo` VALUES ('4', '盘1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\pan1.OSG', null, null, null, null, null, null, null, null, null, '-1');
INSERT INTO `t_modelinfo` VALUES ('5', '盘2', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\pan2.OSG', null, null, null, null, null, null, null, null, null, '1');
INSERT INTO `t_modelinfo` VALUES ('6', '上1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\shang1.OSG', null, null, null, null, null, null, null, null, null, '2');
INSERT INTO `t_modelinfo` VALUES ('7', '下6', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\xia6.OSG', null, null, null, null, null, null, null, null, null, '-2');
INSERT INTO `t_modelinfo` VALUES ('8', '上2', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\shang2.OSG', null, null, null, null, null, null, null, null, null, '3');
INSERT INTO `t_modelinfo` VALUES ('9', '下5', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\xia5.OSG', null, null, null, null, null, null, null, null, null, '-3');
INSERT INTO `t_modelinfo` VALUES ('10', '上3', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\shang3.OSG', null, null, null, null, null, null, null, null, null, '4');
INSERT INTO `t_modelinfo` VALUES ('11', '下4', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\xia4.OSG', null, null, null, null, null, null, null, null, null, '-4');
INSERT INTO `t_modelinfo` VALUES ('12', '上4', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\shang4.OSG', null, null, null, null, null, null, null, null, null, '5');
INSERT INTO `t_modelinfo` VALUES ('13', '下3', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\xia3.OSG', null, null, null, null, null, null, null, null, null, '-5');
INSERT INTO `t_modelinfo` VALUES ('14', '上5', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\shang5.OSG', null, null, null, null, null, null, null, null, null, '6');
INSERT INTO `t_modelinfo` VALUES ('15', '下2', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\xia2.OSG', null, null, null, null, null, null, null, null, null, '-6');
INSERT INTO `t_modelinfo` VALUES ('16', '上6', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\shang6.OSG', null, null, null, null, null, null, null, null, null, '7');
INSERT INTO `t_modelinfo` VALUES ('17', '下1', '0', '0', '0', '0', '1', 'E:\\WorkSpace\\OSGcode\\osg\\xia1.OSG', null, null, null, null, null, null, null, null, null, '-7');
INSERT INTO `t_modelinfo` VALUES ('18', '轴', '0', '0', '0', '0', '3', 'E:\\WorkSpace\\OSGcode\\osg\\zhou.OSG', null, null, null, null, null, null, null, null, null, '8');

-- ----------------------------
-- Table structure for `t_modelprop`
-- ----------------------------
DROP TABLE IF EXISTS `t_modelprop`;
CREATE TABLE `t_modelprop` (
  `iModelID` int(4) NOT NULL,
  `cModelProp` varchar(50) DEFAULT NULL,
  `cModelPropVal` varchar(10) DEFAULT NULL,
  `cMemo` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`iModelID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_modelprop
-- ----------------------------
INSERT INTO `t_modelprop` VALUES ('4', '颜色', '绿色', null);
INSERT INTO `t_modelprop` VALUES ('5', '颜色', '红色', null);
