# vanewindward — Phase 3+ plan

Sequential execution plan for keymap evolution after the Phase 1+2 commit (`e574128`).
Each sub-phase is independent and can be tackled on its own; the only hard
prerequisite is **at least one week of daily use** since the previous change so
muscle memory and any tuning issues have a chance to surface.

---

## Status

| Phase | Scope | State |
|-------|-------|-------|
| 1 | Home-row mods (GACS) + Caps Word + Chordal Hold + Permissive Hold | ✅ done (commit `e574128`) |
| 2 | Layer-tap thumbs for LOWER + RAISE access | ✅ done (commit `e574128`) |
| 3a | Tapping-term tuning + thumb cleanup | planned |
| 3b | Combos | planned |
| 3c | LOWER/RAISE Miryoku-style redesign | planned |
| 4 | Colemak-DH base switch | planned (multi-week commitment) |
| 5 | Full Miryoku adoption | optional, after Phase 4 |

---

## Phase 3a — Tapping-term tuning + thumb cleanup

**Risk:** low. No muscle-memory shift. Each change is one or two keymap lines.

### 3a.1 Tune `TAPPING_TERM`

- Currently `200` in `config.h`.
- Raise to **220** if mods fire on accidental rests (false positives during typing).
- Lower to **180** if intended chords feel slow.
- Tune in 10 ms steps; recompile + reflash + `EE_CLR` between each.

### 3a.2 Drop redundant left-outer-thumb `KC_LALT`

- `keymap.c` BASE thumb row, position 0 (leftmost left thumb).
- Already covered by `HRM_S` (Alt on S-hold) and by Lower's mods.
- Candidates for replacement: `KC_HYPR` (Hyper for app-launcher chords),
  `LT(POINTER, KC_TAB)` for second POINTER access on a thumb, or just
  `XXXXXXX` to leave room for the next idea.

### 3a.3 Drop the pinky `KC_LCTL` fallback

- `keymap.c` BASE row 4 col 0 (bottom-left pinky outer).
- Kept in Phase 1 as a safety net for same-hand Ctrl+C/V/X.
- After ~2 weeks the bilateral-mod habit (use right-hand Ctrl mirror) should be
  automatic — at that point the fallback is just extra surface for accidental
  presses. Replace with `XXXXXXX` or `KC_ESC` duplicate.

### 3a.4 Re-evaluate dual `MS_BTN1` on right thumbs

- Per `dilemma_max_keyboard.md`, `MS_BTN1` is baked on both outer right thumbs
  to compensate for Cirque tap-drift.
- Test: temporarily replace one of them with `XXXXXXX`. Tap-to-click on the
  Cirque should still work (it's enabled in `config.h` via
  `CIRQUE_PINNACLE_TAP_ENABLE`).
- If tap-to-click stayed reliable, reclaim one thumb slot — promising uses:
  `MO(POINTER)` for thumb-driven trackpad layer, or another layer-hold.

---

## Phase 3b — Miryoku-style combos

**Risk:** low. Combos coexist with HRM; only one new file + a `rules.mk` flag.

### Setup

In `rules.mk` add:

    COMBO_ENABLE = yes

Create `keymaps/vanewindward/combos.def` (or define directly in `keymap.c`
under `COMBO_ACTION`).

### Recommended starter combos

| Keys | Output | Why |
|------|--------|-----|
| `J + K` | `Esc` | Vim users already trained, no thumb reach |
| `K + L` | `Enter` | Reduces thumb travel for new lines |
| `F + G` | `Tab` | Left-hand version, no outer-pinky stretch |
| `M + ,` | `Backspace word` (Ctrl/Opt+Bksp) | Faster word-delete than holding mods |
| `D + F` | `Esc` (left-hand duplicate) | If you want symmetry with J+K |

### Tuning

- Set `COMBO_TERM` ~ 40 ms (default 50) — tighter window prevents triggering
  during normal typing rolls.
- Avoid combos on HRM letters together — Chordal Hold + combo timing interact
  awkwardly. Index + middle (J+K) is safe; A+S (both HRM) is risky.

---

## Phase 3c — LOWER/RAISE redesign (Miryoku alignment)

**Risk:** medium. Changes content of two layers but not BASE.

### Goals

- LOWER = SYM (top row) + NUM (right hand) — already close, just clean.
- RAISE = NAV (left hand home row = arrows) + FUN (top row F-keys) — needs
  arrow rearrangement.
- Mirror BASE home-row positions so HRM transfers to layer-hold context.

### Proposed LOWER

    ~   !   @   #   $   %       ^   &   *   (   )   _
    `   1   2   3   4   5       +   7   8   9   *   =
   ___  ⌘   ⌥   ⌃   ⇧   __      -   4   5   6   /   '
   ___  [   ]   {   }   __      .   1   2   3   0   ,
              __  __  __  ___       __  __  __  __

Left hand keeps the backup GACS mods on home row; outer column gets
brackets / pairs rather than RGB controls (RGB rarely used).

### Proposed RAISE (vim-style nav on home row)

       F12 F1  F2  F3  F4  F5      F6  F7  F8  F9  F10 F11
    ___ XX  XX  XX  XX  XX         PgUp Home  ↑  End XX  VolU
    ___ ⌘   ⌥   ⌃   ⇧   XX         PgDn  ←   ↓   →  XX  Mute
    ___ XX  XX  XX  XX  XX         XX   XX   XX  XX XX  VolD
              __  __  __  ___       __  __  __  __

Arrow cluster swapped to right hand (Miryoku/vim convention: H J K L = ← ↓ ↑ →).
Left hand keeps mods so you can chord (e.g. Shift+Arrow for selection).

### Migration order

1. Edit `LAYER_LOWER` array.
2. Build + flash + `EE_CLR` + test with a real symbol-heavy task (write code, fill a form).
3. If feel is right, edit `LAYER_RAISE` array same day.
4. Update `layers.svg` to match.

---

## Phase 4 — Colemak-DH base switch

**Risk:** high productivity cost (4–8 weeks). Highest long-term ROI for RSI +
typing speed.

### Pre-flight checklist

- [ ] Hands fully comfortable with Phase 1–3 (no daily fumbling)
- [ ] 4–8 week window with significant typing time available (essays, code)
- [ ] Backup typing path for urgent work (laptop keyboard with QWERTY, or
      VIA-toggle layer with QWERTY as Layer 5 for emergencies)
- [ ] Typing tutor session daily (Keybr, Monkeytype) — 30 min/day baseline
- [ ] Brief team on temporary slowdown if any meeting/IM workload depends on
      fast response time

### Implementation

- Single edit to `LAYER_BASE` array in `keymap.c`.
- Letter positions change; HRM, Caps Word, layer-taps, Chordal Hold all
  carry over unchanged because they're position-based, not letter-based.

Colemak-DH letter map (positions row 2 / row 3 / row 4 inner ten columns):

    Q W F P B   J L U Y ;
    A R S T G   M N E I O
    Z X C D V   K H , . /

(HRM positions = A R S T on the left, N E I O on the right — same GACS order.)

### Expected curve

| Week | Typing speed (rough) |
|------|----------------------|
| 1 | 15–25 WPM (vs ~70 baseline) |
| 2–3 | 30–40 WPM |
| 4–6 | 50–60 WPM |
| 8 | ~baseline |
| 12+ | exceeds QWERTY baseline |

### Rollback path

- Keep a tagged commit on `develop` before the switch.
- Add a QWERTY fallback layer (`LAYER_QWERTY`) accessible via `TG(LAYER_QWERTY)`
  on a POINTER-layer key. Toggle on for emergency typing.

---

## Phase 5 — Optional: full Miryoku adoption

Only consider after Phase 4 has settled.

- Move to six-layer Miryoku structure: Base, Nav, Mouse, Media, Num, Sym, Fun.
- Each held thumb activates a different layer; one-shot mods on home row of
  every layer for chordal mod access.
- The Procyon's extra columns (vs Miryoku's 36-key target) hold direct-access
  keys (number row, brackets, outer pinky utilities).
- This is mostly a structural reorg; HRM and combos carry over.

---

## Open questions / things to monitor

- Tapping term sweet spot once tuned (`config.h:39`).
- Whether `QUICK_TAP_TERM` should be enabled for arrow/movement keys to allow
  hold-to-repeat (currently uses default; for arrows on RAISE this matters).
- Whether Cirque tap-drift workaround is still needed in 2026 firmware.
- Caps Word edge cases (camelCase identifiers, snake_case underscore).

---

## Workflow reminder (per `qmk_via_eeprom_gotcha.md`)

Every keymap source change requires this full sequence, not just a build:

1. Edit `keymap.c` / `config.h` / `rules.mk` in `~/Documents/qmk_userspace/...`
2. Build:
       cd ~/qmk_firmware && qmk compile -kb bastardkb/dilemma/4x6_4_procyon -km vanewindward
3. Flash left half: double-tap reset, drag UF2 from `.build/` to `/Volumes/RPI-RP2/`
4. Flash right half: swap USB, double-tap reset, drag UF2 again
5. Plug USB back into the designated master half
6. **`EE_CLR`**: hold `Z` + tap `V` — wipes stale EEPROM so VIA reloads from source
7. Test the change end-to-end (BASE letters, mods, Caps Word, both layers)
8. Update `layout.svg` / `layers.svg` if visual changed
9. Commit + push to `VaneWindward/qmk_userspace develop`

Skipping step 6 will silently leave the old layout active — same failure as
2026-05-11 where Phase 1 looked broken until EEPROM was cleared.
