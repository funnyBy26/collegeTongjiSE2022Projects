<template>
  <GlobalLoading>
    <router-view></router-view>
  </GlobalLoading>
</template>

<script setup>
import GlobalLoading from '@/components/GlobalLoading.vue'
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}
</style>
