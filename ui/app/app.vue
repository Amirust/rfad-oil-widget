<template>
  <transition name="fade" mode="out-in">
    <div v-if="oilPercentage > 0 && !!currentOil" style="position: absolute; top: 80%; right: 15px;">
      <div style="position: relative;"  :style="{ opacity: hide ? 0 : 1 }">
        <svg width="50" height="50" viewBox="0 0 50 50" class="circular-progress" id="progress" style="--progress: 100;">
          <circle class="center-bg"></circle>
          <circle class="bg"></circle>
          <circle class="fg" :style="{
            stroke: strokeColor
          }"></circle>
        </svg>
        <template v-if="currentOil === Oil.Black">
          <img style="position: absolute; width: 31px; height: 31px; top: 10px; left: 10px; z-index: 20;" src="~~~/assets/ZD_ICON_TYPE_OIL_BLACK.svg">
        </template>
        <template v-else-if="currentOil === Oil.Corrosion">
          <img style="position: absolute; width: 31px; height: 31px; top: 10px; left: 10px; z-index: 20;" src="~~~/assets/ZD_ICON_TYPE_OIL_COROSION.svg">
        </template>
        <template v-else-if="currentOil === Oil.Fire">
          <img style="position: absolute; width: 31px; height: 31px; top: 10px; left: 10px; z-index: 20;" src="~~~/assets/ZD_ICON_TYPE_OIL_FIRE.svg">
        </template>
        <template v-else-if="currentOil === Oil.Frost">
          <img style="position: absolute; width: 31px; height: 31px; top: 10px; left: 10px; z-index: 20;" src="~~~/assets/ZD_ICON_TYPE_OIL_FROST.svg">
        </template>
        <template v-else-if="currentOil === Oil.Garlic">
          <img style="position: absolute; width: 31px; height: 31px; top: 10px; left: 10px; z-index: 20;" src="~~~/assets/ZD_ICON_TYPE_OIL_GARLICK.svg">
        </template>
        <template v-else-if="currentOil === Oil.Poison">
          <img style="position: absolute; width: 31px; height: 31px; top: 10px; left: 10px; z-index: 20;" src="~~~/assets/ZD_ICON_TYPE_OIL_POISON.svg">
        </template>
        <template v-else-if="currentOil === Oil.Silver">
          <img style="position: absolute; width: 31px; height: 31px; top: 10px; left: 10px; z-index: 20;" src="~~~/assets/ZD_ICON_TYPE_OIL_SILVER.svg">
        </template>
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

:root {
  --oil-black: #CCCECC;
  --oil-corosion: #CCCECC;
  --oil-fire: #CCCECC;
  --oil-frost: #CCCECC;
  --oil-garlic: #CCCECC;
  --oil-poison: #CCCECC;
  --oil-silver: #CCCECC;
}

.circular-progress {
  --size: 45px;
  --half-size: calc(calc(var(--size) / 2) + 3px);
  --stroke-width: 2px;
  --radius: calc((var(--size) - var(--stroke-width)) / 2);
  --circumference: calc(var(--radius) * pi * 2);
  --dash: calc((var(--progress) * var(--circumference)) / 100);
  z-index: 10;
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
.circular-progress circle.center-bg {
  cx: var(--half-size);
  cy: var(--half-size);
  r: calc(var(--radius) + 3px);
  fill: rgba(0,0,0,0.7);
}
.circular-progress circle.fg {
  transform: rotate(90deg) scale(-1, 1);
  transform-origin: var(--half-size) var(--half-size);
  stroke-dasharray: var(--dash) calc(var(--circumference) - var(--dash));
  transition: stroke-dasharray 0.3s linear 0s, stroke 0.3s ease-in-out;
  stroke: transparent;
}
</style>

<script lang="ts" setup>
const hide = ref(false);
/*
:root {
  --oil-black: #97735f;
  --oil-corosion: #bbbd83;
  --oil-fire: #f97355;
  --oil-frost: #657387;
  --oil-garlic: #7f396d;
  --oil-poison: #557b4d;
  --oil-silver: #ffc185;
}
 */
import registerObserver from "~~/composables/registerObserver";

enum Oil {
  Black = 0x480E9071,
  Corrosion = 0x4821913B,
  Fire = 0x4812ae7d,
  Frost = 0x4812FF97 ,
  Garlic = 0x4816cc81,
  Poison = 0x4816CC7E ,
  Silver = 0x480CFAEC ,
}

interface OilUpdateDTO {
  name: string;
  currentCharge: number;
  maxCharge: number;
}

const percentage = (current: number, max: number): number => {
  return (current / max) * 100;
}

const oilPercentage = ref(-1);
const strokeColor = ref('var(--oil-black)');
const currentOil = ref<Oil | null>(null);

const recData = ref<OilUpdateDTO | null>(null);

// onMounted(() => {
//   let charge = 140;
//   setInterval(() => {
//     window.OilUpdate({
//       name: Oil.Fire,
//       currentCharge: charge,
//       maxCharge: 140,
//     })
//     charge -= 1;
//   }, 200)
// })

registerObserver('hide', (data: boolean) => {
  hide.value = data;
})

registerObserver('OilUpdate', (data: OilUpdateDTO) => {
  if (data?.name === 'no_oil') { recData.value = null; currentOil.value = null; oilPercentage.value = -1; return; }

  const id = Number(data.name) as Oil;
  currentOil.value = id;

  switch (id) {
    case Oil.Black:
      strokeColor.value = 'var(--oil-black)';
      break;
    case Oil.Corrosion:
      strokeColor.value = 'var(--oil-corosion)';
      break;
    case Oil.Fire:
      strokeColor.value = 'var(--oil-fire)';
      break;
    case Oil.Frost:
      strokeColor.value = 'var(--oil-frost)';
      break;
    case Oil.Garlic:
      strokeColor.value = 'var(--oil-garlic)';
      break;
    case Oil.Poison:
      strokeColor.value = 'var(--oil-poison)';
      break;
    case Oil.Silver:
      strokeColor.value = 'var(--oil-silver)';
      break;
    default:
      strokeColor.value = 'var(--oil-black)';
  }

  recData.value = data;
  oilPercentage.value = percentage(data.currentCharge, data.maxCharge);
  const progressElement = document.getElementById('progress');
  if (progressElement)
    progressElement.style.setProperty('--progress', `${oilPercentage.value}`);
})
</script>