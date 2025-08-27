<template>
	<div class="container">
		<!-- 左侧部分：实时数据显示 -->
		<div class="left-section">
			<div class="data-card">
				<div class="data-label">心率</div>
				<div style=" border: 2px solid #4ab87d;height: 120px;font-size: 60px;display: flex;justify-content: center; align-items: center; height: 100px;  "
					:class="['data-value', { 'abnormal': heartRate > 100 || heartRate < 60 }]">{{ heartRate }}</div>
			</div>
			<div class="data-card">
				<div class="data-label">血氧</div>
				<div style=" border: 2px solid #4ab87d;height: 120px;font-size: 60px;display: flex;justify-content: center; align-items: center; height: 100px;  "
					:class="['data-value', { 'abnormal': bloodOxygen < 90 }]">{{ bloodOxygen }}</div>
			</div>
			<div class="data-card">
				<div class="data-label">体温</div>
				<div style=" border: 2px solid #4ab87d;height: 120px;font-size: 60px;display: flex;justify-content: center; align-items: center; height: 100px;  "
					:class="['data-value', { 'abnormal': bodyTemperature > 37.3 || bodyTemperature < 36.1 }]">
					{{ bodyTemperature }}</div>
			</div>
		</div>

		<!-- 右侧部分：设备控制 -->
		<div class="right-section">
			<div class="control-card">
				<div class="control-label">蜂鸣器控制</div>
				<el-switch v-model="buzzerStatus" active-color="#13ce66" inactive-color="#ff4949" active-text="开启"
					inactive-text="关闭"></el-switch>
			</div>
		</div>
	</div>
</template>

<script>
	export default {
		data() {
			return {
				heartRate: 75,
				bloodOxygen: 96,
				bodyTemperature: 36.9,
				buzzerStatus: false
			};
		}
	};
</script>

<style scoped>
	.container {
		display: flex;
		justify-content: space-between;
		padding: 20px;
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
	}

	.data-card {
		/* flex: 1; */
		height: 180px;
		/* background-color: #89e8fa; */
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
</style>