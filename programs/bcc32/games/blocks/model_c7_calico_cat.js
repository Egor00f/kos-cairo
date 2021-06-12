// block name, color, step, coord: x,y,z, rotation: x,y,z

const m1 = 0xffffff; //белый
const m2 = 0x9e5d1a; //коричневый
const m3 = 0x080808; //черный
const m4 = 0xff8080; //

model_list=[
['b2x3x1', m1, 0,  4, -16, 6, 0,0,90],
['b2x3x1', m1, 0, 0, -8, 6, 0,0,90],
['b2x2x1', m1, 0,  4, -8, 6, 0,0,0],
['b2x3x1', m1, 0,  4, 0, 6, 0,0,90],
['b2x3x1', m1, 0,-12, 4, 6, 0,0,0],
['b2x3x1', m1, 0,  4, 8, 6, 0,0,90],
['b2x3x1', m1, 0,  8, 4, 6, 0,0,0],
['b2x3x1', m1, 0,  8, 16, 6, 0,0,90],
['b2x2x1', m1, 0, -8, 16, 6, 0,0,0],
['b1x3x1', m1,  1,  4, -16, 9, 0,0,90],
['b2x3x1', m1,  1, 0, -12, 9, 0,0,90],
['b2x2x1', m2,  1,  8, -12, 9, 0,0,90],
['b2x2x1', m1,  1, -8, -4, 9, 0,0,0],
['b2x3x1', m1,  1,  8, -4, 9, 0,0,90],
['b2x3x1', m1,  1, -4, 4, 9, 0,0,90],
['b2x3x1', m1,  1, -4, 12, 9, 0,0,90],
['b2x3x1', m1,  1, 12, 4, 9, 0,0,90],
['b2x3x1', m1,  1, 12, 12, 9, 0,0,90],
['b1x1x1', m1,  1, 0, 16, 9, 0,0,0],
['b1x1x1', m1,  1, -8, 20, 9, 0,0,0],
['b1x2x1', m3,  1, 0, 20, 9, 0,0,90],
['b1x2x1', m1,  1,  8, 20, 9, 0,0,90],
['b1x3x1', m1,  2, 0, -20, 12, 0,0,0],
['b1x2x1', m1,  2, -4, -16, 12, 0,0,0],
['b1x2x1', m1,  2,  4, -16, 12, 0,0,0],
['a1x2x2', m3,  2, -8, -8, 12, 0,0,180],
['a1x2x2', m2,  2,  8, -8, 12, 0,0,180],
['t2x3x1', m1,  2, -4, -4, 12, 0,0,180],
['t2x3x1', m1,  2,  4, -4, 12, 0,0,0],
['b2x3x1', m1,  2,-12, 0, 12, 0,0,0],
['b2x3x1', m1,  2,  8, 0, 12, 0,0,0],
['a1x2x3', m3,  2,-12, 12, 12, 0,0,0],
['a1x2x2', m1,  2, -8, 16, 12, 0,0,0],
['a1x2x2', m3,  2, -4, 16, 12, 0,0,0],
['a1x2x2', m3,  2, 0, 16, 12, 0,0,0],
['a1x2x2', m1,  2,  4, 16, 12, 0,0,0],
['a1x2x2', m1,  2,  8, 16, 12, 0,0,0],
['a1x2x3', m2,  2, 12, 12, 12, 0,0,0],
['f1x3x1', m3,  3,  4,-20, 15, 0,0,90],
['f1x3x1', m1,  3,  4,-16, 15, 0,0,90],
['b1x3x1', m1,  3,  4,-12, 15, 0,0,90],
['b1x2x1', m3,  3, -8, -8, 15, 0,0,0],
['b2x2x1', m1,  3, -4, -8, 15, 0,0,0],
['b2x2x1', m2,  3,  4, -8, 15, 0,0,0],
['b2x3x1', m1,  3, -4,  0, 15, 0,0,90],
['b2x3x1', m1,  3,  8,  0, 15, 0,0,90],
['b1x2x1', m3,  3, 12,  0, 15, 0,0,0],
['b2x2x1', m2,  3,-12,  8, 15, 0,0,0],
['b2x3x1', m1,  3,  4, 12, 15, 0,0,90],
['b2x2x1', m1,  3,  8,  8, 15, 0,0,0],
['b1x1x1', m3,  3, -8, 16, 15, 0,0,0],
['b1x1x1', m1,  3,  8, 16, 15, 0,0,0],
['f1x2x1', m1,  4,  2,-16, 18, 0,0,90],
['b1x1x1', m1,  4, -8, -4, 18, 0,0,0],
['a1x3x2', m1,  4, -4, -4, 18, 0,0,180],
['a1x3x2', m1,  4,  0, -4, 18, 0,0,180],
['a1x3x2', m1,  4,  4, -4, 18, 0,0,180],
['b1x1x1', m1,  4,  8, -4, 18, 0,0,0],
['a1x2x2', m1,  4, -8,  0, 18, 0,0,90],
['a1x2x2', m1,  4, -8,  4, 18, 0,0,90],
['a1x2x2', m3,  4, -8,  8, 18, 0,0,90],
['b2x3x1', m1,  4, -4,  0, 18, 0,0,0],
['b1x3x1', m1,  4,  4,  0, 18, 0,0,0],
['a1x2x2', m3,  4,  8,  0, 18, 0,0,-90],
['a1x2x2', m3,  4,  8,  4, 18, 0,0,-90],
['a1x2x2', m1,  4,  8,  8, 18, 0,0,-90],
['b1x1x1', m2,  4,-12, 12, 18, 0,0,0],
['b1x1x1', m1,  4, 12, 12, 18, 0,0,0],
['a1x2x2', m2,  4, -8, 12, 18, 0,0,0],
['a1x2x2', m2,  4, -4, 12, 18, 0,0,0],
['a1x2x2', m3,  4,  0, 12, 18, 0,0,0],
['a1x2x2', m3,  4,  4, 12, 18, 0,0,0],
['a1x2x2', m1,  4,  8, 12, 18, 0,0,0],
['b1x1x1', m2,  5, -8,  0, 21, 0,0,0],
['b2x2x1', m2,  5, -4, -4, 21, 0,0,0],
['b1x1x1', m1,  5,  4, -4, 21, 0,0,0],
['b1x2x1', m3,  5,  8,  0, 21, 0,0,90],
['b1x2x1', m3,  5,  8,  4, 21, 0,0,90],
['b1x2x1', m1,  5, -4,  4, 21, 0,0,90],
['b1x3x1', m1,  5,  0,  4, 21, 0,0,0],
['b2x2x1', m2,  5, -8,  8, 21, 0,0,0],
['b2x2x1', m1,  5,  4,  8, 21, 0,0,0],
['b1x2x1', m1,  6,  4, -12, 3, 0,0,0],
['b1x3x1', m1,  6,  0, -16, 3, 0,0,0],
['b1x2x1', m1,  6, -4, -12, 3, 0,0,0],
['b2x3x1', m1,  6,  4,  4, 3, 0,0,90],
['b1x3x1', m1,  6,  8,  8, 3, 0,0,0],
['b1x3x1', m1,  6,  4, 12, 3, 0,0,0],
['b1x2x1', m1,  6,  0, 12, 3, 0,0,0],
['a1x2x2', m2,  6,  0, 20, 3, 0,0,0],
['b1x3x1', m1,  6, -4, 12, 3, 0,0,0],
['b1x3x1', m1,  6, -8,  8, 3, 0,0,0],
['u1x2x1', m1,  7, -4,-30, 6, 0,0,90],
['u1x2x1', m1,  7, -4,-26, 6, 0,0,90],
['b1x3x1', m1,  8, -8,-30, 9, 0,0,0],
['f1x3x1', m1,  8, -4,-34, 9, 0,0,0],
['f1x3x1', m3,  9, -8,-30, 12, 0,0,0],
['b1x3x1', m1,  9, -4,-28, 12, 0,0,0],
['c1x1x1', m3, 10, -4,-32, 12, 0,0,0],
['c1x1x1', m3, 10, -4,-32, 15, 0,0,0],
['f1x2x1', m1, 11,  2,-34, 6, 0,0,90],
['f1x3x1', m1, 11,  0,-30, 6, 0,0,0],
['f1x3x1', m4, 12,  0,-36, 9, 0,0,0],
['t2x3x1', m1, 12,  0,-20, 9, 0,0,-90],
['f1x2x1', m1, 13,  0,-34, 12, 0,0,0],
['a1x2x2', m2, 13,  0,-28, 15, 0,0,180],
['u1x2x1', m1, 14, 4,-30, 6, 0,0,-90],
['u1x2x1', m1, 14, 4,-26, 6, 0,0,-90],
['b1x3x1', m1, 15, 8,-30, 9, 0,0,0],
['f1x3x1', m1, 15, 4,-34, 9, 0,0,0],
['f1x3x1', m2, 16, 8,-30, 12, 0,0,0],
['b1x3x1', m1, 16, 4,-28, 12, 0,0,0],
['c1x1x1', m3, 17, 4,-32, 12, 0,0,0],
['c1x1x1', m2, 17, 4,-32, 15, 0,0,0],
['a1x2x2', m3, 18, -4,-28, 15, 0,0,90],
['a1x2x2', m2, 18,  4,-28, 15, 0,0,-90],
['b1x3x1', m2, 18, -2,-24, 15, 0,0,90],
['b1x3x1', m3, 18, 10,-24, 15, 0,0,90],
['f1x3x1', m3, 19,  4,-28, 18, 0,0,90],
['b1x2x1', m3, 19,  2,-24, 18, 0,0,90],
['a1x2x2', m3, 19, 10,-24, 18, 0,0,90],
['a1x2x2', m2, 19,-10,-24, 18, 0,0,-90],
['b1x1x1', m3, 20, 10,-24, 21, 0,0,0],
['b1x1x1', m3, 20,-10,-24, 21, 0,0,0],
['b1x1x1', m2, 21, 10,-24, 24, 0,0,0],
['b1x1x1', m2, 21,-10,-24, 24, 0,0,0],
['c1x3x1', m1, 22,  4,-20, 0, 0,0,0],
['c1x3x1', m1, 22, -4,-20, 0, 0,0,0],
['c1x4x1', m1, 22,  8,  0, 0, 0,0,0],
['c1x4x1', m1, 22, -8,  0, 0, 0,0,0],
['b2x3x1', m1, 22,  4,  8, 0, 0,0,90],
['t2x3x1', m1, 22,  0, 16, 0, 0,0,90],
['c1x3x1', m2, 22,  0, 24,  0, 0,0,-45],
['c1x4x1', m3, 23,  0,  8,  3, 0,0,-45, 1],
['c1x4x1', m3, 23,  0, 12, -3, 0,0,-45, 2],
['c1x4x1', m3, 23,  0, 12,  3, 0,0,-45, 3],
];

model_animat=[
[132,'rotation','z','*1', -0.883572934,0.883572934,.09817477],
[133,'rotation','z','*2', -0.883572934,0.883572934,.09817477],
[134,'rotation','z','*3', -0.883572934,0.883572934,.09817477],
[135,'rotation','z','*4', -0.883572934,0.883572934,.09817477],
];
