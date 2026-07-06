<template>
  <div class="register">
    <div class="fixed-menu">
      <MenuBar/>
    </div>
    <div class="register">
      <RegisterPage/>
    </div>
  </div>
  
</template>

<script>
import MenuBar from "@/components/MenuBar.vue"
import RegisterPage from "@/components/RegisterPage.vue";

export default {
  name: "RegisterView",
  components: {
    RegisterPage,
    MenuBar
  },
};
</script>

<style scoped>
.fixed-menu {
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  z-index: 1000;
  background-color: white;
}

.register{
  margin-top: 8%;
}
</style>