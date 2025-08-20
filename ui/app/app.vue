<template>
  <transition name="fade" mode="out-in">
    <div v-if="oilPercentage > 0" style="position: absolute; top: 80%; right: 10px;">
      <div style="position: relative;">
        <svg
            width="50" height="50" viewBox="0 0 50 50"
            class="circular-progress" id="progress" style="--progress: 100;"
        >
          <circle class="bg"></circle>
          <circle class="fg"></circle>
        </svg>
        <img style="position: absolute; width: 31px; height: 31px; top: 10px; left: 10px;" src="~~~/assets/ZD_ICON_TYPE_OIL_BLACK.svg">
      </div>
    </div>
  </transition>
</template>

<style>
.fade-enter-active,
.fade-leave-active {
  transition: opacity 0.5s ease;
}

.fade-enter-from,
.fade-leave-to {
  opacity: 0;
}

.circular-progress {
  --size: 50px;
  --half-size: calc(var(--size) / 2);
  --stroke-width: 3px;
  --radius: calc((var(--size) - var(--stroke-width)) / 2);
  --circumference: calc(var(--radius) * pi * 2);
  --dash: calc((var(--progress) * var(--circumference)) / 100);
}
.circular-progress circle {
  cx: var(--half-size);
  cy: var(--half-size);
  r: var(--radius);
  stroke-width: var(--stroke-width);
  fill: none;
  stroke-linecap: round;
}
.circular-progress circle.bg {
  stroke: transparent;
}
.circular-progress circle.fg {
  transform: rotate(-90deg);
  transform-origin: var(--half-size) var(--half-size);
  stroke-dasharray: var(--dash) calc(var(--circumference) - var(--dash));
  transition: stroke-dasharray 0.3s linear 0s;
  stroke: #FFB86A;
}
</style>

<script lang="ts" setup>
import registerObserver from "~~/composables/registerObserver";

interface OilUpdateDTO {
  name: string;
  currentCharge: number;
  maxCharge: number;
}

const percentage = (current: number, max: number): number => {
  return (current / max) * 100;
}

const oilPercentage = ref(-1);

const recData = ref<OilUpdateDTO | null>(null);

// onMounted(() => {
//   const progressElement = document.getElementById('progress');
//   if (progressElement) {
//     progressElement.style.setProperty('--progress', `${oilPercentage.value}`);
//   }
//
//   setInterval(() => {
//     oilPercentage.value -= 0.3;
//     const progressElement = document.getElementById('progress');
//     if (progressElement) {
//       progressElement.style.setProperty('--progress', `${oilPercentage.value}`);
//     }
//
//     if (oilPercentage.value <= 0) {
//       oilPercentage.value = 100;
//     }
//   }, 300);
// })

registerObserver('OilUpdate', (data: OilUpdateDTO) => {
  recData.value = data;
  oilPercentage.value = percentage(data.currentCharge, data.maxCharge);
  const progressElement = document.getElementById('progress');
  if (progressElement) {
    progressElement.style.setProperty('--progress', `${oilPercentage.value}`);
  }
})
</script>