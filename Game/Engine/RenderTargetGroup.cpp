#include "pch.h"
#include "RenderTargetGroup.h"
#include "Engine.h"
#include "Device.h"

void RenderTargetGroup::Create(RENDER_TARGET_GROUP_TYPE groupType, vector<RenderTarget>& rtVec, shared_ptr<Texture> dsTexture)
{
	_groupType = groupType;
	_rtVec = rtVec;
	_rtCount = static_cast<uint32>(rtVec.size());
	_dsTexture = dsTexture;

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NumDescriptors = _rtCount;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	heapDesc.NodeMask = 0;

	DEVICE->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&_rtvHeap));

	_rtvHeapSize = DEVICE->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	_rtvHeapBegin = _rtvHeap->GetCPUDescriptorHandleForHeapStart();
	_dsvHeapBegin = _dsTexture->GetDSV()->GetCPUDescriptorHandleForHeapStart();

	for (uint32 i = 0; i < _rtCount; i++)
	{
		uint32 destSize = 1;
		D3D12_CPU_DESCRIPTOR_HANDLE destHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(_rtvHeapBegin, i * _rtvHeapSize);

		uint32 srcSize = 1;
		ComPtr<ID3D12DescriptorHeap> srcRtvHeapBegin = _rtVec[i].target->GetRTV();
		D3D12_CPU_DESCRIPTOR_HANDLE srcHandle = srcRtvHeapBegin->GetCPUDescriptorHandleForHeapStart();

		DEVICE->CopyDescriptors(1, &destHandle, &destSize, 1, &srcHandle, &srcSize, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}
}
