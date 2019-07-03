/////////////////////////////////////////////////////////////////////////
///@file FasexMarketApi.h
///@brief ����������ͻ���API�ӿ�
/////////////////////////////////////////////////////////////////////////

#ifndef FASEX_MARKETAPI_H
#define FASEX_MARKETAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FasexApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_FASEX_MARKET_API_EXPORT
#define FASEX_MARKET_API_EXPORT __declspec(dllexport)
#else
#define FASEX_MARKET_API_EXPORT __declspec(dllimport)
#endif
#else
#define FASEX_MARKET_API_EXPORT 
#endif

class CFasexMarketSpi
{
public:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected(){};
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ���������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason){};
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///���Ļص���ʼ֪ͨ����API�յ�һ�����ĺ����ȵ��ñ�������Ȼ���Ǹ�������Ļص�������Ǳ��Ļص�����֪ͨ��
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///���Ļص�����֪ͨ����API�յ�һ�����ĺ����ȵ��ñ��Ļص���ʼ֪ͨ��Ȼ���Ǹ�������Ļص��������ñ�������
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};


	///����Ӧ��
	virtual void OnRspError(CFasexRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û���¼Ӧ��
	virtual void OnRspUserLogin(CFasexRspUserLoginField *pRspUserLogin, CFasexRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û��˳�Ӧ��
	virtual void OnRspUserLogout(CFasexRspUserLogoutField *pRspUserLogout, CFasexRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ӧ��
	virtual void OnRspSubscribeTopic(CFasexDisseminationField *pDissemination, CFasexRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Լ��ѯӦ��
	virtual void OnRspQryInstrument(CFasexRspInstrumentField *pRspInstrument, CFasexRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Լ����״̬��ѯӦ��
	virtual void OnRspQryInstrumentStatus(CFasexInstrumentStatusField *pInstrumentStatus, CFasexRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯӦ��
	virtual void OnRspQryTopic(CFasexDisseminationField *pDissemination, CFasexRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CFasexInstrumentStatusField *pInstrumentStatus) {};

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CFasexDepthMarketDataField *pDepthMarketData) {};

	///���������ʱ��Ӧ��
	virtual void OnRspMarketTime(CFasexMarketDateTimeField *pMarketDateTime, CFasexRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
};

class FASEX_MARKET_API_EXPORT  CFasexMarketApi
{
public:
	///����MduserApi
	///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
	///@return ��������UserApi
	static CFasexMarketApi *CreateMarketApi(const char *pszFlowPath = "");
	
	///��ȡϵͳ�汾��
	///@param nMajorVersion ���汾��
	///@param nMinorVersion �Ӱ汾��
	///@return ϵͳ��ʶ�ַ���
	static const char *GetVersion();
	
	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release() = 0;
	
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init() = 0;
	
	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join() = 0;
	
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char *GetTradingDay() = 0;
	
	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp����������Э�飬��127.0.0.1��������������ַ����17001�������������˿ںš�
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp����������Э�飬��127.0.0.1��������������ַ����12001�������������˿ںš�
	///@remark RegisterFront������RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(CFasexMarketSpi *pSpi) = 0;
	
	///����֤��
	///@param pszCertFileName �û�֤���ļ���
	///@param pszKeyFileName �û�˽Կ�ļ���
	///@param pszCaFileName ������CA֤���ļ���
	///@param pszKeyFilePassword �û�˽Կ�ļ�����
	///@return 0 �����ɹ�
	///@return -1 ������CA֤������ʧ��
	///@return -2 �û�֤������ʧ��
	///@return -3 �û�˽Կ����ʧ��	
	///@return -4 �û�֤��У��ʧ��
	virtual int RegisterCertificateFile(const char *pszCertFileName, const char *pszKeyFileName, 
		const char *pszCaFileName, const char *pszKeyFilePassword) = 0;

	///�����г����顣
	///@param nTopicID �г���������  
	///@param nResumeType �г������ش���ʽ  
	///        FASEX_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        FASEX_TERT_RESUME:���ϴ��յ�������
	///        FASEX_TERT_QUICK:�ȴ��͵�ǰ�������,�ٴ��͵�¼���г����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribeMarketDataTopic(int nTopicID, FASEX_TE_RESUME_TYPE nResumeType) = 0;

	///����������ʱʱ�䡣
	///@param timeout ������ʱʱ��(��)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;


	///�û���¼����
	virtual int ReqUserLogin(CFasexReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

	///�û��˳�����
	virtual int ReqUserLogout(CFasexReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///������������
	virtual int ReqSubscribeTopic(CFasexDisseminationField *pDissemination, int nRequestID) = 0;

	///��Լ��ѯ����
	virtual int ReqQryInstrument(CFasexQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///��Լ����״̬��ѯ����
	virtual int ReqQryInstrumentStatus(CFasexQryInstrumentStatusField *pQryInstrumentStatus, int nRequestID) = 0;

	///�����ѯ����
	virtual int ReqQryTopic(CFasexDisseminationField *pDissemination, int nRequestID) = 0;

	///���������ʱ������
	virtual int ReqMarketTime(CFasexMarketDateTimeField *pMarketDateTime, int nRequestID) = 0;
protected:
	~CFasexMarketApi(){};
};

#endif