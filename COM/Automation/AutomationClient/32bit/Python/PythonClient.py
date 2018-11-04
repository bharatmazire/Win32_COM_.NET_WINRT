import comtypes.client as cc
import comtypes
tlb_id = comtypes.GUID("{A52E59B2-8BBA-4479-9B18-D38F821ABCFC}") #Type Lib GUID

cc.GetModule((tlb_id, 1, 0)) # 1 and 0 are major number and minor number of our Type Lib

import comtypes.gen.AutomationServerTypeLib as AutomationServer #AutomationServerWithRegFileLib2 is Type lib name specified in IDL file


pIMyMath = cc.CreateObject("{8FD1609B-35AF-4E51-9D6B-B8F17998AF3A}",  None, None, AutomationServer.IMyMath) #Passed CoClass ID(clsid) and Interface name


result=pIMyMath.SumOfTwoIntegers(25,20)
print "Sum of 25 and 20 is:"+ str(result)
print "Requesting IMyMath using pIMyMath"
pIMyMath2=pIMyMath.QueryInterface(AutomationServer.IMyMath)

result2=pIMyMath.SubtractionOfTwoIntegers(250,100)
print "Subtraction of 250 and 100 is:"+ str(result2)