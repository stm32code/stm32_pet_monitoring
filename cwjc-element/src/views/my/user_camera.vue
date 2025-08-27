<template>
	<div>
		<baidu-map class="bm-view" ak="XXX" :center="mapCenter" :zoom="mapZoom" :scroll-wheel-zoom="true"
			@ready="onReady" @click="getClickInfo" />
	</div>
</template>

<script>
	import BaiduMap from 'vue-baidu-map/components/map/Map.vue'
	const defaultInfo = {
		lng: 0,
		lat: 0,
		addressStr: '',
		title: '',
		province: '', // 省
		city: '', // 市
		district: '' // 区
	}
	export default {
		name: 'MapMaker',
		components: {
			BaiduMap
		},
		data() {
			return {
				ssq: {
					provinceName: '',
					cityName: '',
					districtName: ''
				},
				BMap: null,
				map: null,
				mapZoom: 15,
				mapCenter: {
					lng: 121.329402,
					lat: 31.228667
				},
				keyword: '',
				searchResult: [], // 检索结果列表
				showResultFlag: true,
				selectInfo: Object.assign({}, defaultInfo)
			}
		},
		created() {
			
		},
		methods: {
			// 地图初始化回调
			onReady({
				BMap,
				map
			}) {
				this.BMap = BMap
				this.map = map
				this.getClickInfo()
			},
		
			handleSelect(item) {
			},
			handleSubmit() {
				this.$emit('submitAddressFun', this.keyword)
			},
			// 在地图上选取
			getClickInfo(e) {
				const BMapGL = this.BMap
				const map = this.map
				map.clearOverlays()
				const marker = new BMapGL.Marker(
					new BMapGL.Point(121.338528, 31.231631)
				)
				map.addOverlay(marker)
				
			}
		}
	}
</script>

<style lang="scss" scoped>
	.map-maker-wrapper {
		position: relative;
	}

	.btn-confrim {
		width: 120px;
		height: 56px;
		line-height: 56px;
		background-color: #5ac9d4;
		border-radius: 8px;
		color: #ffffff;
		text-align: center;
	}

	.bm-view {
		//   margin-top: 30px;
		width: 100%;
		height: calc(100vh - 88px);
	}

	.search-wrap {
		position: relative;
		width: 350px;
		box-sizing: border-box;
		padding: 0 32px;

		.search {
			z-index: 5;
			width: 450px;
			height: 30px;
			position: absolute;
			top: -66px;
			left: 30%;
		}

		.search input {
			float: left;
			width: 350px;
			height: 100%;
			border: 1px solid #30ccc1;
			padding: 0 8px;
			outline: none;
		}

		.search button {
			float: left;
			/*width: 20%;*/
			height: 100%;
			background: #30ccc1;
			border: 1px solid #30ccc1;
			color: #fff;
			outline: none;
		}

		.search-result {
			position: absolute;
			top: -34px;
			left: 30%;
			width: 406px;
			z-index: 5;
			background-color: #fff;
			padding: 0 32px;
			border-radius: 10px;
			max-height: 420px;
			overflow-y: scroll;

			.item {
				border-bottom: 1px solid #ebeef2;

				//   padding: 32px 0;
				&:last-child {
					border-bottom: none;
				}

				.title {
					font-size: 14px;
					font-weight: 600;
					color: #313233;
					margin: 10px 0 5px;
				}

				.address {
					font-size: 12px;
					font-weight: 400;
					color: #9ca5b3;
					margin: 5px 0 10px;
					// margin-top: 8px;
				}
			}
		}
	}
</style>