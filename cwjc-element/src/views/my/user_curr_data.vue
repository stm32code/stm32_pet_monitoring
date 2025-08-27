<template>
	<div class="container">
		<!-- 左侧部分：实时数据显示 -->
		<div class="left-section">
			<div class="data-card">
				<div class="data-label">心率</div>
				<div style=" border: 2px solid #4ab87d;height: 60px;font-size: 60px;display: flex;justify-content: center; align-items: center; height: 100px;  "
					:class="['data-value', { 'abnormal': heartRate > 100 || heartRate < 60 }]">{{ heartRate }}</div>
			</div>
			<div class="data-card">
				<div class="data-label">血氧</div>
				<div style=" border: 2px solid #4ab87d;height: 60px;font-size: 60px;display: flex;justify-content: center; align-items: center; height: 100px;  "
					:class="['data-value', { 'abnormal': bloodOxygen < 90 }]">{{ bloodOxygen }}</div>
			</div>
			<div class="data-card">
				<div class="data-label">体温</div>
				<div style=" border: 2px solid #4ab87d;height: 60px;font-size: 60px;display: flex;justify-content: center; align-items: center; height: 100px;  "
					:class="['data-value', { 'abnormal': bodyTemperature > 40 || bodyTemperature < 20 }]">
					{{ bodyTemperature }}
				</div>
			</div>
	
			<div class="data-card">
				<div class="data-label">经纬度</div>
				<div class="abnormal" style=" color: green;border: 2px solid #4ab87d;height: 90px;font-size: 40px;display: flex;justify-content: center; align-items: center; height: 100px;  "
					>
					{{ jwd }}
				</div>
			</div>
		</div>

		<!-- 右侧部分：设备控制 -->
		<div class="right-section">
			<div class="control-card" style="background-color: #89e8fa;border-radius: 8px;">
				<div class="control-label">蜂鸣器控制</div>
				<el-button @click="setCon('1')" :loading="loading" type="primary"
					style="width:30%;margin-top: 10px;margin-left: 18%;">打开</el-button>
				<el-button @click="setCon('0')" :loading="loading" type="primary"
					style="width:30%;margin-top: 10px;">关闭</el-button>
			</div>
			<div class="control-card" style="">
				<baidu-map class="bm-view" ak="XXX" :center="mapCenter" :zoom="mapZoom" :scroll-wheel-zoom="true"
					@ready="onReady" @click="getClickInfo" />
			</div>
		</div>
	</div>
</template>

<script>
	import myAxios from "@/api/my";
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
				selectInfo: Object.assign({}, defaultInfo),
				heartRate: 75,
				bloodOxygen: 96,
				bodyTemperature: 38.9,
				buzzerStatus: false,
				jwd: '',
			};
		},
		created() {
			this.getData(this.device)
			// this.getDeviceDataList()
			this.timer = setInterval(() => {
				this.getData(this.device)
				// this.getDeviceDataList()
			}, 2000)

		},
		beforeDestroy() {
			if (this.timer) {
				clearInterval(this.timer); //关闭
				console.log("定时器销毁")
			} //利用vue的生命周期函数
		},
		methods: {
			setCon(val) {
				myAxios.setContro('', val).then(resp => {
					console.log(resp)
					if (resp.code === 20000) {
						this.$message.success(resp.message)
					} else {
						this.$message.error(resp.message);
					}
				})
			},
			getData(device) {
				myAxios.getCurrData(device).then(resp => {
					console.log(resp)
					if (resp.code === 20000) {
						// this.$message.success(resp.message)
						this.bodyTemperature = resp.data.tw
						this.heartRate = resp.data.xl
						this.bloodOxygen = resp.data.xy
						let jd = resp.data.jd
						let wd = resp.data.wd
						this.jwd = jd + ' , '+ wd
						this.mapCenter.lat = wd
						this.mapCenter.lng = jd
						const BMapGL = this.BMap
						const map = this.map
						map.clearOverlays()
						const marker = new BMapGL.Marker(
							new BMapGL.Point(jd, wd)
						)
						map.addOverlay(marker)

					} else {
						this.$message.error(resp.message);
					}

				})
			},
			// 地图初始化回调
			onReady({
				BMap,
				map
			}) {
				this.BMap = BMap
				this.map = map
				this.getClickInfo()
			},

			handleSelect(item) {},
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
	};
</script>

<style lang="scss" scoped>
	$bg: #2d3a4b;
	$dark_gray: #889aa4;
	$light_gray: #eee;
	
	.login-container {
		// min-height: 100%;
		// width: 100%;
		// background-color: $bg;
		// overflow: hidden;
	
		width: 100%;
		height: 100%;
		background-image: url("./img/bj.jpg");
		background-size: cover;
		background-position: center;
		position: relative;
	
	
		.login-form {
			position: relative;
			width: 520px;
			max-width: 100%;
			padding: 160px 35px 0;
			margin: 0 auto;
			overflow: hidden;
		}
	
		.tips {
			font-size: 14px;
			color: #fff;
			margin-bottom: 10px;
	
			span {
				&:first-of-type {
					margin-right: 16px;
				}
			}
		}
	
		.svg-container {
			padding: 6px 5px 6px 15px;
			color: $dark_gray;
			vertical-align: middle;
			width: 30px;
			display: inline-block;
		}
	
		.title-container {
			position: relative;
	
			.title {
				font-size: 26px;
				color: $light_gray;
				margin: 0px auto 40px auto;
				text-align: center;
				font-weight: bold;
			}
		}
	
		.show-pwd {
			position: absolute;
			right: 10px;
			top: 7px;
			font-size: 16px;
			color: $dark_gray;
			cursor: pointer;
			user-select: none;
		}
	}
	.container {
		display: flex;
		justify-content: space-between;
		padding: 20px;
		width: 100%;
		height: 100%;
		background-image: url("./img/bj.jpg");
		background-size: cover;
		background-position: center;
		position: relative;
			
	}

	.left-section {
		display: flex;
		flex-direction: column;
		justify-content: space-between;
		/* flex-grow: 1; */
		background-color: #dde6fa;
		border-radius: 8px;
		box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);
		padding: 20px;
		width: 50%;
	}

	.right-section {
		/* width: 200px; */
		background-color: #e9f8fa;
		border-radius: 8px;
		box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);
		padding: 20px;
		width: 50%;
		margin-left: 10px;
	}

	.data-card {
		/* flex: 1; */
		height: 150px;
		// background-color: #89e8fa; 
		margin-top: 20px;
	}

	.data-label {
		font-size: 14px;
		color: #666;
	}

	.data-value {
		font-size: 24px;
		margin-top: 10px;
		color: green;
	}

	.data-value.abnormal {
		color: #ff4949;
	}

	.control-card {
		padding: 20px;
	}

	.control-label {
		font-size: 16px;
		color: #666;
	}



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
		height: 65vh;
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