

function sysCall_init()
    
    modelHandle = sim.getObject('.')
    
    -- check if the haptic plugin is loaded
    moduleName = 0
    moduleVersion = 0
    index = 0
    pluginNotFound = true
    while (moduleName) do
        moduleName, moduleVersion = sim.getModuleName(index)
        if (moduleName=='CHAI3D') then
            pluginNotFound = false
        end
        index = index+1
    end

    if (pluginNotFound) then
        sim.displayDialog('Error', 'CHAI3D plugin was not found, or was not correctly initialized (v_repExtCHAI3D.dll).', sim.dlgstyle_ok, false, nil, {0.8, 0, 0, 0, 0, 0}, {0.5, 0, 0, 1, 1, 1})
    else
        local device =0
        local toolRadius = 0.3
        workspaceRadius = 0.2
        if (simCHAI3D.start(device, toolRadius, workspaceRadius) == -1) then
            sim.displayDialog('Error', 'Device failed to initialize.', sim.dlgstyle_ok, false, nil, {0.8, 0, 0, 0, 0, 0}, {0.5, 0, 0, 1, 1, 1})
        else
            CHAI3DPluginInitialized = true

            simBase=sim.getObject('/LBR_iiwa_7_R800')
            
            simTip=sim.getObject('/tip')
            simTarget=sim.getObject('/target')
            
            --[[
            -- Joint Velocity Initializer
            graphVel=sim.getObjectHandle('GraphVel')
            
            
            j1VelStream=sim.addGraphStream(graphVel,'joint 1 velocity','deg/s',0,{1,0,0})
            j2VelStream=sim.addGraphStream(graphVel,'joint 2 velocity','deg/s',0,{0,1,0})
            j3VelStream=sim.addGraphStream(graphVel,'joint 3 velocity','deg/s',0,{0,0,1})
            j4VelStream=sim.addGraphStream(graphVel,'joint 4 velocity','deg/s',0,{1,1,0})
            j5VelStream=sim.addGraphStream(graphVel,'joint 5 velocity','deg/s',0,{1,0,1})
            j6VelStream=sim.addGraphStream(graphVel,'joint 6 velocity','deg/s',0,{0,1,1})
            j7VelStream=sim.addGraphStream(graphVel,'joint 7 velocity','deg/s',0,{1,0.5,0})
            
            -----
            
            -- Joint Acceleration Initializer
            graphAccel=sim.getObjectHandle('GraphAccel')
            
            
            j1AccelStream=sim.addGraphStream(graphAccel,'x acceleration','m/s^2',0,{1,0,0})
            sim.setGraphStreamTransformation(graphAccel,j1AccelStream,sim.stream_transf_derivative)
            j2AccelStream=sim.addGraphStream(graphAccel,'y acceleration','m/s^2',0,{0,1,0})
            sim.setGraphStreamTransformation(graphAccel,j2AccelStream,sim.stream_transf_derivative)
            
            j3AccelStream=sim.addGraphStream(graphAccel,'x acceleration','m/s^2',0,{0,0,1})
            sim.setGraphStreamTransformation(graphAccel,j3AccelStream,sim.stream_transf_derivative)
            j4AccelStream=sim.addGraphStream(graphAccel,'y acceleration','m/s^2',0,{1,1,0})
            sim.setGraphStreamTransformation(graphAccel,j4AccelStream,sim.stream_transf_derivative)
            
            j5AccelStream=sim.addGraphStream(graphAccel,'x acceleration','m/s^2',0,{1,0,1})
            sim.setGraphStreamTransformation(graphAccel,j5AccelStream,sim.stream_transf_derivative)
            j6AccelStream=sim.addGraphStream(graphAccel,'y acceleration','m/s^2',0,{0,1,1})
            sim.setGraphStreamTransformation(graphAccel,j6AccelStream,sim.stream_transf_derivative)
            
            j7AccelStream=sim.addGraphStream(graphAccel,'x acceleration','m/s^2',0,{1,0.5,0})
            sim.setGraphStreamTransformation(graphAccel,j7AccelStream,sim.stream_transf_derivative)
            ------------------------
            
            
            objectPosX = sim.addGraphStream(graphVel, 'object pos x', 'm', 1)
            objectPosY = sim.addGraphStream(graphVel, 'object pos y', 'm', 1)
            
            sim.addGraphCurve(graphVel,'object pos x/y',2,{objectPosX,objectPosY},{0,0},'m by m')
            --]]
            
            -- initializer q0(7X1) and JH0(3X7)
            q0 = Matrix( 7, 1, {0, math.pi/6, 0, -math.pi/6, 0, math.pi/6, 0} )
                      
            JH0 = Matrix( 3, 7, { 1.1921e-04, 0.5464, -5.9605e-05, -0.2000, 0, 5.9605e-05, -5.9605e-05,
                                0.7465, 0.0617, 0.2233, -0.0280, 0.1089, 0.0079, 0.0077,
                                2.3842e-04, -0.6600, 0, 0.4587, -4.7684e-04, -0.1112, -5.9605e-05 }
                        )
            
            q = q0
            q_pre = q
            
            JH = JH0
            JH_pre = JH
            
            -- get joint handles
            jointHandles={}
            for i=1,7,1 do
                jointHandles[i]=sim.getObject('/LBR_iiwa_7_R800_joint'..i)
                --sim.setJointTargetPosition(jointHandles[i],q0[i])
            end
            
            pd_pre = simExtCHAI3D_readPosition(0)
            
            --startPos = sim.getObjectPosition(simTarget, modelHandle)
            
            sim.setObjectPosition(simTarget, modelHandle, pd_pre)
            
            pd_pre = sim.getObjectPosition(simTarget, modelHandle)
            
            
            xd_pre = Matrix( 3, 1, {pd_pre[1], pd_pre[2], pd_pre[3]} )
            
            
            tau = 0.2
            mu = 0.1
            alp = 0.1
            gamma = 0.1
            
            dq_pre = Matrix( 7, 1, {0, 0, 0, 0, 0, 0, 0} )
            
            -- the actual end-effector position corresponding to the q0 
            xa_pre = Matrix( 3, 1, {0.5404, -0.3782, 0.8069} )
           
            va_pre = Matrix( 3, 1, {0, 0, 0} )
            
            -- filter variables
            dq_fp = Matrix( 7, 1, {0, 0, 0, 0, 0, 0, 0} )
            xa_fp = xa_pre
            va_fp = Matrix( 3, 1, {0, 0, 0} )
            
            counter = 0
            t1 = sim.getSimulationTime()
            
        end
    end
end 


function sysCall_actuation()
    
    --simIK.applyIkEnvironmentToScene(ikEnv,ikGroup)
    
end



function sysCall_sensing()
    -- Pseudo inverse of matrix
    --[[
        (m < n): (A_R)^-1 = (A^T)*((A*A^T)^-1)
        (m > n): (A_L)^-1 = ((A^T*A)^-1)*A^T
    --]]
    
    -- Read the position of the cursor:
    pd = simCHAI3D.readPosition(0)
    
    print("-------haptic position--------")
        
    local info = string.format("position:\nx : %.8f, \ty : %.8f, \tz : %.8f\n", pd[1], pd[2], pd[3])
    sim.addLog(sim.verbosity_scriptinfos, info)
    
    print("------------------------------")
    
    
    
    --targetPos = sim.getObjectPosition(simTarget, modelHandle)
    
    --deltaPos = { pd[1]-pd_pre[1], pd[2]-pd_pre[2], pd[3]-pd_pre[3] }
    
    --newPos = { targetPos[1]+deltaPos[1], targetPos[2]+deltaPos[2], targetPos[3]+deltaPos[3] }
    
    sim.setObjectPosition(simTarget, modelHandle, pd)
    
    pd = sim.getObjectPosition(simTarget, modelHandle)
    
    xd = Matrix( 3, 1, {pd[1], pd[2], pd[3]} )
    
    --counter = counter + 1
    
    bStated = simCHAI3D.readButtons(0)
    
    if CHAI3DPluginInitialized and (xd ~= xd_pre) then
        
        
        t2 = sim.getSimulationTime()
        dt = t2 - t1
        t1 = t2
        -- the desire velocity
        vd = (xd - xd_pre)/dt
        
        
        -- get the actual position of the dummyTip
        pa = sim.getObjectPosition(simTip, modelHandle)
        xa = Matrix( 3, 1, {pa[1], pa[2], pa[3]} )
        

        JH_T = JH:t()
        I_JH = Matrix:eye(3)
        
        -- 3X3
        JH_sq = JH*JH_T + 0.01*I_JH    -- square matrix
        
        --JH_sd = JH_sq:det()    -- square det
        --print("------------------")
        --print("JH_sd = ", JH_sd)
        --[[
        if math.abs(JH_sd) < (1e-11) then
            JH_sq = JH_sq + 0.01*I_JH
        end 
        --]]
        --print(JH_sq:det())
        --print("------------------")
        ---------------------------
        
        -- 7X3
        JH_inv = JH_T*(JH_sq:inv())
        
        dq = JH_inv*(vd + gamma*(xd-xa))
        -- dq = (JH:t())*(md-ma);
        
        
        --- Initializer variables
        dq_f = (1-tau/alp)*dq_fp + (tau/alp)*dq_pre
        ddq_f = (dq - dq_f)/alp
        
        xa_f = (1-tau/alp)*xa_fp + (tau/alp)*xa_pre
        va = (xa - xa_f)/alp
        
        va_f = (1-tau/alp)*va_fp + (tau/alp)*va_pre
        dva = (va - va_f)/alp
        
        
        
        -- 1X1
        dq_T = dq:t()
        I_dq = Matrix:eye(1)
        
        dq_sq = dq_T*dq + 0.01*I_dq    -- square matrix
        
        --dq_sd = dq_sq:det()    -- square det
        --print("***********************")
        --print("dq_sd = ", dq_sd)
        --[[if math.abs(dq_sd) < (1e-11) then
            dq_sq = dq_sq + 0.01*I_dq
        end--]] 
        --print(dq_sq:det())
        --print("***********************")
        
        
        dq_inv = (dq_sq:inv())*dq_T
        dJH = (dva - JH*ddq_f + gamma*(va - JH*dq))*dq_inv
        
        
        q = q_pre + tau*dq
        
        
        JH = JH_pre + tau*dJH
        
        
        if MatrixNorm(JH - JH_pre) > 0.01 then
            JH = JH_pre
        end
        
        for i=1,7,1 do
            sim.setJointTargetPosition(jointHandles[i],q[i])
        end 
            
        
        --deltaPos = { xd[1]-xd_pre[1], xd[2]-xd_pre[2], xd[3]-xd_pre[3] }
        --local p = sim.getObjectPosition(simTarget, -1)
        
        --newPos = { p[1]+deltaPos[1], p[2]+deltaPos[2], p[3]+deltaPos[3] }
        
        --sim.setObjectPosition(simTarget, -1, newPos)
        
        --I = I_pre + tau*mu*(md - ma)
        --I* = I*_pre + tau*mu*(v - JH*dq)
        
        q_pre = q
        JH_pre = JH
        pd_pre = pd
        xd_pre = xd
        dq_pre = dq
        
        xa_pre = xa
        va_pre = va
        
        dq_fp = dq_f
        xa_fp = xa_f
        va_fp = va_f
        --I_pre = I
        --I*_pre = I*
        
        
        --[[
        -- Set Velocity GraphStreamValue
        sim.setGraphStreamValue(graphVel,j1VelStream,180*sim.getJointVelocity(jointHandles[1])/math.pi)
        sim.setGraphStreamValue(graphVel,j2VelStream,180*sim.getJointVelocity(jointHandles[2])/math.pi)
        sim.setGraphStreamValue(graphVel,j3VelStream,180*sim.getJointVelocity(jointHandles[3])/math.pi)
        sim.setGraphStreamValue(graphVel,j4VelStream,180*sim.getJointVelocity(jointHandles[4])/math.pi)
        sim.setGraphStreamValue(graphVel,j5VelStream,180*sim.getJointVelocity(jointHandles[5])/math.pi)
        sim.setGraphStreamValue(graphVel,j6VelStream,180*sim.getJointVelocity(jointHandles[6])/math.pi)
        sim.setGraphStreamValue(graphVel,j7VelStream,180*sim.getJointVelocity(jointHandles[7])/math.pi)
        ---
        
        -- Set Accel GraphStreamValue
        
        sim.setGraphStreamValue(graphAccel,j1AccelStream,180*sim.getJointVelocity(jointHandles[1])/math.pi)
        sim.setGraphStreamValue(graphAccel,j2AccelStream,180*sim.getJointVelocity(jointHandles[2])/math.pi)
        sim.setGraphStreamValue(graphAccel,j3AccelStream,180*sim.getJointVelocity(jointHandles[3])/math.pi)
        sim.setGraphStreamValue(graphAccel,j4AccelStream,180*sim.getJointVelocity(jointHandles[4])/math.pi)
        sim.setGraphStreamValue(graphAccel,j5AccelStream,180*sim.getJointVelocity(jointHandles[5])/math.pi)
        sim.setGraphStreamValue(graphAccel,j6AccelStream,180*sim.getJointVelocity(jointHandles[6])/math.pi)
        sim.setGraphStreamValue(graphAccel,j7AccelStream,180*sim.getJointVelocity(jointHandles[7])/math.pi)
       
        ---
        
        local pos=sim.getObjectPosition(simTip,-1)
        sim.setGraphStreamValue(graphVel,objectPosX,pos[1])
        sim.setGraphStreamValue(graphVel,objectPosY,pos[2])
        --]]
    end    
    
end


function sysCall_cleanup()
    if (CHAI3DPluginInitialized) then
        simCHAI3D.reset()
        
    end
    
    --sim.resetGraph(graphVel)
    --sim.resetGraph(graphAccel)
    --simIK.eraseEnvironment(ikEnv)
    
end




addSphere=function(rad,pos)
    if CHAI3DPluginInitialized then
        local sphereHandle=sim.createPureShape(1,4+16,{rad*2,rad*2,rad*2},1)
        sim.setObjectParent(sphereHandle,modelHandle,true)
        sim.setObjectPosition(sphereHandle,modelHandle,pos)
        return addMesh(sphereHandle,true), sphereHandle
    end
    return -1, -1
end

addMesh=function(shapeHandle,whenRemovedEraseMesh)
    if CHAI3DPluginInitialized then
        if not objCont then
            objCont={}
        end
        objCont[#objCont+1]=shapeHandle
        local vertices,indices=sim.getShapeMesh(shapeHandle)
        local pos=sim.getObjectPosition(shapeHandle,modelHandle)
        local orient=sim.getObjectOrientation(shapeHandle,modelHandle)
        local hapticObjId=simCHAI3D.addShape(vertices,indices,pos,orient,1000)
        objCont[#objCont+1]=hapticObjId
        objCont[#objCont+1]=whenRemovedEraseMesh
        return hapticObjId
    end
    return -1
end
setObjectPose=function(objectHandle,pos,orient,interpolTimeInMs)
    if CHAI3DPluginInitialized then
        if objCont then
            for i=1,(#objCont)/3,1 do
                local shapeHandle=objCont[3*(i-1)+1]
                local fdObj=objCont[3*(i-1)+2]
                if fdObj==objectHandle then
                    sim.setObjectPosition(shapeHandle,modelHandle,pos)
                    sim.setObjectOrientation(shapeHandle,modelHandle,orient)
                    simCHAI3D.updateShape(fdObj,pos,orient,1000)
                    return
                end
            end
        end
    end
end


MatrixNorm = function(m)
    
    if getmetatable(m) == Matrix then
        local s=0
        row = m:rows()
        col = m:cols()
        for i=1,row do
            for j=1,col do
                s = s + m:get(i, j)*m:get(i, j)
            end
        end
        
        return math.sqrt(s)
    end

end
