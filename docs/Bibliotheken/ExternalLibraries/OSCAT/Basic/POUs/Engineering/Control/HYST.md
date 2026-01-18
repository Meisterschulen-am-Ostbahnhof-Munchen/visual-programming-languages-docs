# HYST

```{index} single: HYST
```

Hystereses function

This Hystereses function has two modes:
1. if on > off then Q will be switched high when in > on and switched low when in < off.
2. if on < off then Q will be switched high when in < on and switched low when in > off.
the output win will be high when in is between low and high.

## 🎧 Podcast

* [Das Relais im Detail: Schaltverstärker, Schutz und die Geheimnisse von A1/A2, 85/86 und der Hysterese](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Das-Relais-im-Detail-Schaltverstrker--Schutz-und-die-Geheimnisse-von-A1A2--8586-und-der-Hysterese-e3audsc)

## 📺 Video

* [Das Relais im Detail: Schaltverstärker, Schutz und die Geheimnisse von A1/A2, 85/86 und der Hyste...](https://www.youtube.com/watch?v=OUNlE4NABX4)

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| REQ | | IN, ONN, OFF |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| CNF | | Q, WIN |

### Input Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| IN | REAL | |
| ONN | REAL | |
| OFF | REAL | |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| Q | BOOL | |
| WIN | BOOL | |