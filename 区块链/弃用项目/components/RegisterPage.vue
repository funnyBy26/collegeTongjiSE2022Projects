<template>
  <div class="register-page">
     
    <!-- 主要内容区域 -->
    <div class="main-content">
      <div class="header" >
        <h1>预约挂号
          <el-button type="primary" @click="goToAppointment">确认</el-button>
        </h1>
      </div>

      <!-- 左侧医院列表 -->
      <div class="list-content">  
        <div class="hospital-list">
          <h2>选择医院</h2>
          <!-- 当前地区医院 -->
          <div class="hospital-section" v-if="currentRegionHospitals.length">
            <div class="section-title">
              <span>当前用户所在地区：  {{ currentRegion }}</span>
            </div>
            <div class="custom-radio-group">
              <div
                v-for="hospital in currentRegionHospitals"
                :key="hospital.id"
                class="custom-radio"
                  :class="{
                  'selected': selectedHospital === hospital.id,
                  'disabled': !isHospitalAvailable(hospital.id)
                }"
                @click="handleHospitalClick(hospital.id)"
              >
                <span class="hospital-name">{{ hospital.name }}</span>
                <span class="hospital-address">{{ hospital.address }}</span>
              </div>
            </div>
          </div>

          <!-- 其他地区医院 -->
          <div class="hospital-section" v-for="(hospitals, region) in otherRegionHospitals" :key="region">
            <div class="section-title">{{ region }}</div>
            <div class="custom-radio-group">
              <div
                v-for="hospital in hospitals"
                :key="hospital.id"
                class="custom-radio"
                :class="{
                  'selected': selectedHospital === hospital.id,
                  'disabled': !isHospitalAvailable(hospital.id)
                }"
                  @click="handleHospitalClick(hospital.id)"
              >
                <span class="hospital-name">{{ hospital.name }}</span>
                <span></span>
                <span class="hospital-address">{{ hospital.address }}</span>
              </div>
            </div>
          </div>
        </div>

        <!-- 右侧项目列表 -->
        <div class="service-list">
          <h2>选择项目</h2>
          <el-radio-group v-model="selectedService" @change="handleServiceChange">
            <el-radio 
              v-for="service in services" 
              :key="service.id" 
              :label="service.id"
              :disabled="!isServiceAvailable(service.id)"
              @click="handleServiceClick(service.id)"
            >
              {{ service.name }}
            </el-radio>
          </el-radio-group>
        </div>
    </div>
    </div>

    <!-- 快速挂号浮窗 -->
    <div class="quick-register">
      <h3>快速挂号</h3>
      <el-form :model="quickRegisterForm" label-width="80px">
        <el-form-item label="选择医院">
          <el-autocomplete
            v-model="quickRegisterForm.hospitalKeyword"
            :fetch-suggestions="queryHospitals"
            placeholder="请输入医院名称"
            @select="handleHospitalSelect"
          />
        </el-form-item>

        <el-form-item label="选择项目">
          <el-select 
            v-model="quickRegisterForm.serviceId"
            placeholder="请选择项目"
            :disabled="!quickRegisterForm.hospitalId"
            @change="handleQuickServiceSelect"
          >
            <el-option
              v-for="service in availableServices"
              :key="service.id"
              :label="service.name"
              :value="service.id"
            />
          </el-select>
        </el-form-item>

        <el-form-item label="选择医生">
          <el-select
            v-model="quickRegisterForm.doctorId"
            placeholder="请选择医生"
            :disabled="!quickRegisterForm.serviceId"
          >
            <el-option
              v-for="doctor in availableDoctors"
              :key="doctor.id"
              :label="doctor.name"
              :value="doctor.id"
            />
          </el-select>
        </el-form-item>

        <el-form-item label="选择日期">
          <el-date-picker
            v-model="quickRegisterForm.date"
            type="date"
            placeholder="请选择日期"
            :disabled="!quickRegisterForm.doctorId"
            :disabled-date="disabledDate"
            @change="handleDateChange"
          />
        </el-form-item>

        <el-form-item label="选择时段">
          <el-select
            v-model="quickRegisterForm.timeSlotId"
            placeholder="请选择时段"
            :disabled="!quickRegisterForm.date"
          >
            <el-option
              v-for="slot in availableTimeSlots"
              :key="slot.id"
              :label="slot.time + ' (剩余' + slot.remaining + '号)'"
              :value="slot.id"
              :disabled="slot.remaining <= 0"
            />
          </el-select>
        </el-form-item>

        <el-form-item>
          <el-button type="primary" @click="submitQuickRegister">提交预约</el-button>
        </el-form-item>
      </el-form>
    </div>
  </div>
</template>

<script setup>
import { ref, computed } from 'vue'
import { ElMessage } from 'element-plus'
import { useRouter } from 'vue-router'
import dayjs from 'dayjs'

// 模拟当前位置
const currentRegion = ref('上海市')

const router = useRouter()
// 扩展医院数据结构
const hospitals = ref([
  { id: 1, name: '仁爱医院', region: '上海市', address: '浦东新区张江路123号' },
  { id: 2, name: '同济医院', region: '上海市', address: '普陀区新村路789号' },
  { id: 3, name: '北京协和医院', region: '北京市', address: '东城区帅府园1号' },
  { id: 4, name: '广东省人民医院', region: '广东省', address: '广州市越秀区中山二路106号' },
  { id: 5, name: '华山医院', region: '上海市', address: '静安区乌鲁木齐中路12号' },
  { id: 6, name: '北京友谊医院', region: '北京市', address: '宣武区永安路95号' },
  { id: 7, name: '中山医院', region: '上海市', address: '徐汇区枫林路180号' },
  { id: 8, name: '中山医院', region: '上海市', address: '徐汇区枫林路180号' }
])

const services = ref([
  { id: 1, name: '牙齿美白', hospitals: [1, 2, 5, 8] },
  { id: 2, name: '牙齿矫正', hospitals: [1, 3, 6, 7] },
  { id: 3, name: '补牙', hospitals: [1, 2, 3, 4, 5, 6, 7, 8] },
  { id: 4, name: '拔牙', hospitals: [1, 2, 3, 4, 5, 6, 7, 8] },
  { id: 5, name: '种植牙', hospitals: [1, 2, 3] },
  { id: 6, name: '根管治疗', hospitals: [1, 2, 3, 5, 6, 7, 8] },
  { id: 7, name: '牙周病治疗', hospitals: [2, 3, 4, 5, 6, 7, 8] },
  { id: 8, name: '牙齿修复', hospitals: [1, 4, 5, 6, 7] },

])

const doctors = ref([
  { id: 1 , name: '张医生', hospitalId: 1, serviceIds: [1, 2, 3, 6, 7, 8] },
  { id: 2 , name: '李医生', hospitalId: 1, serviceIds: [2, 3, 4] },
  { id: 3 , name: '王医生', hospitalId: 2, serviceIds: [1, 3] },
  { id: 4 , name: '赵医生', hospitalId: 2, serviceIds: [2, 3, 6] },
  { id: 5 , name: '孙医生', hospitalId: 3, serviceIds: [1, 3] },
  { id: 6 , name: '周医生', hospitalId: 4, serviceIds: [2, 3, 5, 8] },
  { id: 7 , name: '吴医生', hospitalId: 5, serviceIds: [1, 3, 6, 7] },
  { id: 8 , name: '郑医生', hospitalId: 6, serviceIds: [2, 5, 8] },
  { id: 9 , name: '陈医生', hospitalId: 7, serviceIds: [1, 6, 7] },
  { id: 10, name: '刘医生', hospitalId: 8, serviceIds: [2, 3, 5] },
])

// 选中的医院和项目
const selectedHospital = ref('')
const selectedService = ref('')

// 快速挂号表单
const quickRegisterForm = ref({
  hospitalKeyword: '',
  hospitalId: '',
  serviceId: '',
  doctorId: '',
  date: '',
  timeSlotId: ''
})

// 获取当前地区的医院
const currentRegionHospitals = computed(() => {
  return hospitals.value.filter(hospital => hospital.region === currentRegion.value)
})

// 获取其他地区的医院（按地区分组）
const otherRegionHospitals = computed(() => {
  const groups = {}
  hospitals.value
    .filter(hospital => hospital.region !== currentRegion.value)
    .forEach(hospital => {
      if (!groups[hospital.region]) {
        groups[hospital.region] = []
      }
      groups[hospital.region].push(hospital)
    })
  return groups
})  

// 计算可用的服务列表
const availableServices = computed(() => {
  if (!quickRegisterForm.value.hospitalId) return []
  return services.value.filter(service => 
    service.hospitals.includes(quickRegisterForm.value.hospitalId)
  )
})

// 计算可用的医生列表
const availableDoctors = computed(() => {
  if (!quickRegisterForm.value.hospitalId || !quickRegisterForm.value.serviceId) return []
  return doctors.value.filter(doctor => 
    doctor.hospitalId === quickRegisterForm.value.hospitalId &&
    doctor.serviceIds.includes(quickRegisterForm.value.serviceId)
  )
})

// 检查服务是否可用
const isServiceAvailable = (serviceId) => {
  if (!selectedHospital.value) return true
  const service = services.value.find(s => s.id === serviceId)
  return service.hospitals.includes(selectedHospital.value)
}

// 检查医院是否可用
const isHospitalAvailable = (hospitalId) => {
  if (!selectedService.value) return true
  const service = services.value.find(s => s.id === selectedService.value)
  return service.hospitals.includes(hospitalId)
}

// 添加点击处理函数
const handleHospitalClick = (hospitalId) => {
  if (!isHospitalAvailable(hospitalId)) return
  if (selectedHospital.value === hospitalId) {
    selectedHospital.value = ''
  } else {
    selectedHospital.value = hospitalId
  }
}

const handleServiceClick = (serviceId) => {
  if (!isServiceAvailable(serviceId)) return
  if (selectedService.value === serviceId) {
    selectedService.value = ''
  } else {
    selectedService.value = serviceId
  }
}

// 搜索医院建议
const queryHospitals = (queryString, cb) => {
  const results = queryString
    ? hospitals.value.filter(hospital => 
        hospital.name.toLowerCase().includes(queryString.toLowerCase())
      )
    : hospitals.value
  cb(results.map(hospital => ({
    value: hospital.name,
    id: hospital.id
  })))
}

// 处理医院选择
const handleHospitalSelect = (item) => {
  quickRegisterForm.value.hospitalId = item.id
  quickRegisterForm.value.serviceId = ''
  quickRegisterForm.value.doctorId = ''
}

// 处理快速挂号服务选择
const handleQuickServiceSelect = () => {
  quickRegisterForm.value.doctorId = ''
}

//禁选日期
const disabledDate = (time) => {
  const today = dayjs().startOf('day')
  const maxDate = today.add(7, 'day')
  return time.getTime() < today.valueOf() || time.getTime() > maxDate.valueOf()
}

// 可用时段列表
const availableTimeSlots = ref([])

// 模拟获取可用时段的API调用
const fetchAvailableTimeSlots = async () => {
  try {
    // 这里应该是实际的API调用
    // const response = await api.getTimeSlots({
    //   hospitalId: quickRegisterForm.value.hospitalId,
    //   serviceId: quickRegisterForm.value.serviceId,
    //   doctorId: quickRegisterForm.value.doctorId,
    //   date: quickRegisterForm.value.date
    // })
    
    // 模拟数据
    const mockTimeSlots = [
      { id: 1, time: '09:00-09:30', remaining: 3 },
      { id: 2, time: '09:30-10:00', remaining: 0 },
      { id: 3, time: '10:00-10:30', remaining: 5 },
      { id: 4, time: '10:30-11:00', remaining: 2 },
      { id: 5, time: '14:00-14:30', remaining: 0 },
      { id: 6, time: '14:30-15:00', remaining: 4 },
    ]
    availableTimeSlots.value = mockTimeSlots
  } catch (error) {
    ElMessage.error('获取可用时段失败')
    availableTimeSlots.value = []
  }
}

// 处理日期变化
const handleDateChange = () => {
  quickRegisterForm.value.timeSlotId = ''
  if (quickRegisterForm.value.date) {
    fetchAvailableTimeSlots()
  }
}

// 修改提交快速挂号验证
const submitQuickRegister = () => {
  if (!quickRegisterForm.value.hospitalId || 
      !quickRegisterForm.value.serviceId || 
      !quickRegisterForm.value.doctorId ||
      !quickRegisterForm.value.date ||
      !quickRegisterForm.value.timeSlotId) {
    ElMessage.warning('请完整填写挂号信息')
    return
  }
  // 这里添加提交逻辑
  ElMessage.success('预约成功')
}
const goToAppointment = () => {
  router.push('/register/appointment')
}
</script>

<style scoped>
.register-page {
  padding: 20px;
  position: relative;
  min-height: calc(100vh - 120px);
}

.main-content {
  display: flex;
  flex-direction: column;
  gap: 20px;
  margin-right: 22%;
  background: #fdfdfd;
  padding: 20px;
  border-radius: 8px;
  box-shadow: 0 4px 18px 0 rgba(0, 0, 0, 0.228);
}

.header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding-bottom: 5px;
  border-bottom: 2px solid #eee;
  border-bottom-color: rgb(94, 148, 254);
}

.list-content {
  display: flex;
  gap: 20px;
}

.hospital-list,
.service-list {
  flex: 1;
  padding: 20px;
  position: relative;
}

.hospital-list h2,
.service-list h2 {
  margin-bottom: 20px;
  color: #333;
  text-align: left;
}

.custom-radio-group {
  display: flex;
  flex-direction: column;
  gap: 12px;
  width: 100%;
}

.custom-radio {
  padding: 12px 15px;
  border: 1px solid #DCDFE6;
  border-radius: 4px;
  cursor: pointer;
  transition: all 0.3s;
  text-align: left;
  width: 100%;
  box-sizing: border-box;
  font-size: 14px;
  line-height: 1.4;
  display: flex;
  align-items: center;
}

.custom-radio:hover:not(.disabled) {
  border-color: #409EFF;
  color: #409EFF;
  background-color: #ecf5ff;
}

.custom-radio.selected {
  background-color: #409EFF;
  color: white;
  border-color: #409EFF;
  font-weight: 500;
}

.custom-radio.disabled {
  background-color: #F5F7FA;
  border-color: #E4E7ED;
  color: #C0C4CC;
  cursor: not-allowed;
}

.quick-register {
  position: fixed;
  top: 150px;
  right: 20px;
  width: 300px;
  background: #e0edfc;
  padding: 20px;
  border-radius: 8px;
  box-shadow: 0 2px 12px 0 rgba(0,0,0,0.1);
}

.quick-register h3 {
  margin-bottom: 20px;
  color: #333;
}

.hospital-section {
  margin-bottom: 24px;
}

.section-title {
  font-size: 18px;
  text-align: left;
  color: #909399;
  margin-bottom: 12px;
  padding-left: 4px;
  border-left: 3px solid #409EFF;
}

.hospital-name {
  font-weight: 600;
  font-size: 16px;
  text-align: left;
}

.hospital-address {
  font-size: 15px;
  color: #909399;
  margin-left: 8px;
}

/* 滚动条样式 */
.hospital-list {
  max-height: 600px;
  overflow-y: auto;
}

.hospital-list::-webkit-scrollbar {
  width: 6px;
}

.hospital-list::-webkit-scrollbar-thumb {
  background-color: #E4E7ED;
  border-radius: 3px;
}

.hospital-list::-webkit-scrollbar-track {
  background-color: #F5F7FA;
}
</style>
