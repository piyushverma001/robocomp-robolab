/*
 *    Copyright (C)2018 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{
    setPeriod(33);
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
       astra::terminate();
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{

    depthB = QString::fromStdString(params["depth"].value).contains("true");
	colorB = QString::fromStdString(params["color"].value).contains("true");


    astra::initialize();
    reader = new astra::StreamReader(streamSet.create_reader());
    frameListener = new MultiFrameListener(*reader);
	timer.start(Period);
//    initializeStreams();
    frameListener->set_color_stream(true);
    frameListener->set_depth_stream(true);
    frameListener->set_point_stream(true);
    reader->add_listener(*frameListener);
	return true;
}

void SpecificWorker::compute()
{
	QMutexLocker locker(mutex);
    astra_update();
}


Registration SpecificWorker::getRegistration()
{
//implementCODE

}

void SpecificWorker::getData(imgType &rgbMatrix, depthType &distanceMatrix, RoboCompJointMotor::MotorStateMap &hState, RoboCompGenericBase::TBaseState &bState)
{
//implementCODE
//	RGBMutex->lock();
//	rgbMatrix=*colorImage;
//	RGBMutex->unlock();
//	depthMutex->lock();
//	distanceMatrix=*depthImage;
//	depthMutex->unlock();
    qDebug()<<"Trying to get data";
    frameListener->get_color(rgbMatrix);
    frameListener->get_depth(distanceMatrix);

}

void SpecificWorker::getXYZ(PointSeq &points, RoboCompJointMotor::MotorStateMap &hState, RoboCompGenericBase::TBaseState &bState)
{
//implementCODE
    frameListener->get_points(points);
}

void SpecificWorker::getRGB(ColorSeq &color, RoboCompJointMotor::MotorStateMap &hState, RoboCompGenericBase::TBaseState &bState)
{
//implementCODE
    frameListener->get_color(color);
}

TRGBDParams SpecificWorker::getRGBDParams()
{
//implementCODE
    qDebug()<<"getRGBDParams Not implemented yet";
}

void SpecificWorker::getDepth(DepthSeq &depth, RoboCompJointMotor::MotorStateMap &hState, RoboCompGenericBase::TBaseState &bState)
{
//implementCODE
    frameListener->get_depth(depth);
}

void SpecificWorker::setRegistration(const Registration &value)
{
//implementCODE
    qDebug()<<"setRegistration Not implemented yet";
}

void SpecificWorker::getImage(ColorSeq &color, DepthSeq &depth, PointSeq &points, RoboCompJointMotor::MotorStateMap &hState, RoboCompGenericBase::TBaseState &bState)
{
//implementCODE
    frameListener->get_color(color);
    frameListener->get_depth(depth);
    frameListener->get_points(points);
}

void SpecificWorker::getDepthInIR(depthType &distanceMatrix, RoboCompJointMotor::MotorStateMap &hState, RoboCompGenericBase::TBaseState &bState)
{
    qDebug()<<"getDepthInIR Not implemented yet";
}
