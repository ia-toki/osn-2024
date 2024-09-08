This workflow is currently written in only Bahasa Indonesia.

## OSN Workflow

1. Untuk setiap soal, terdapat sebuah **slug** soal, yakni, kode nama soal. Slug pada soal-soal OSN Tahun X ini telah disepakati bersama dan mengikuti format berikut: `osn-<X>-<judul-soal-singkat>`. Contoh: `osn-2024-xyz`.

2. Apabila belum pernah dilakukan, *clone* repositori ini, kemudian pastikan Anda sudah berada di direktori `osn-2024-problems`:
  ```
  git clone git@github.com:ia-toki/osn-2024-problems.git
  cd osn-2024-problems
  ```

3. Jika ingin mengerjakan suatu komponen di suatu soal, buat branch dengan format `<slug>-<komponen>`. Contoh: `osn-2024-xyz-solution`. Caranya:
  ```
  git checkout master
  git checkout -b osn-2024-xyz-solution
  ```

4. Kerjakan komponen pada branch tersebut dan pada direktori yang sesuai yaitu `<slug>`. Satu branch hanya untuk satu komponen saja.

5. Penamaan komponen dan berkas untuk masing-masing komponen:
  - `description`: `description-id.html`, `description-en.html`, `render/`, `helper/`
  - `solution`: `solution.cpp`
  - `runner`: `spec.cpp`
  - `scorer`: `scorer.cpp`
  - `communicator`: `communicator.cpp`
  - `solution-<subtask-number>`: `solution-<subtask-number>.cpp` (misalnya, `solution-1.cpp`)
  - `alt-solution-<author>`: `solution-<author>-ac-<solution-name>` (misalnya, `solution-athin-ac-maxflow`)
  - `<verdict>-solution-<author>`: `solution-<author>-<verdict>-<solution-name>` (misalnya, `solution-athin-tle-bf`)

6. Bila sudah selesai, add, kemudian commit. Ingat, hanya commit source code/text, jangan executablenya! Format commit messagenya terserah, yang penting informatif. Contoh:
  ```
  git add osn-2024-xyz/solution.cpp
  git commit -m "Add solution for OSN 2024 Problem XYZ"
  ```

7. Push ke origin:
  ```
  git push origin osn-2024-xyz-solution
  ```

8. Buka [https://github.com/ia-toki/osn-2024-problems/pulls](https://github.com/ia-toki/osn-2024-problems/pulls).
  - Buat pull request baru dari branch tersebut ke master serta beri label `<slug>` dan `<komponen>`.
  - Assign reviewer ke salah satu anggota SC OSN lainnya.

9. Reviewer akan memberikan review dan komentar.
10. Jika Anda ingin memperbaiki, dapat dilakukan dengan commit lagi ke branch tersebut, lalu push lagi. Merge requestnya akan ter-update dengan sendirinya.
11. Jika dirasa sudah selesai, Anda dapat menghubungi Koordinator SC OSN untuk merge branch tersebut ke master.

***

### Notes

#### Examples

- Contoh paling ringkas dapat dilihat pada [dokumentasi tcframe](https://tcframe.toki.id/en/stable/getting-started/getting-started.html).
- Contoh berkas OSN tahun-tahun sebelumnya dapat dilihat di [https://github.com/orgs/ia-toki/repositories?q=osn](https://github.com/orgs/ia-toki/repositories?q=osn).

#### General Information

- Usahakan mempelajari git sendiri. Namun jika ada kesulitan, bisa hubungi anggota SC OSN lainnya.
- Karena kode akan di-review SC OSN lain, mohon koding serapi mungkin.
- Jika Anda merasa tidak dapat menyelesaikan sebuah komponen yang dialokasikan pada Anda, beritahu Koordinator SC OSN secepatnya sehingga akan dialokasikan kepada SC OSN lainnya (termasuk Koordinator SC OSN).

#### Runner

- Gunakan [tcframe](https://github.com/ia-toki/tcframe) 1.6.0.
- Kecuali memang benar-benar perlu berubah, gunakan **Time Limit 1 detik** dan **Memory Limit 256 MB**.
- Test case tidak perlu terlalu banyak. Yang penting meng-cover banyak tricky case.
  - Sebisa mungkin total tc untuk seluruh subtask tidak melebihi **100 pasang**.
  - Sebisa mungkin total ukuran berkas seluruh tc tidak melebihi **50 MB**.
- Untuk mengimport tcframe, gunakan `#include "tcframe/runner.hpp"`. Jangan `#include "runner.hpp"`, atau `#include "../tcframe/runner.hpp"`, ataupun yang lainnya. Karena nantinya Koordinator SC OSN akan men-generate testcase menggunakan include folder tersebut.
- Jika ingin menggunakan [tcrand](https://github.com/afaji/tcrand), letakkan folder `tcrand` satu level dengan folder `tcframe` dan edit `tcframe/scripts/tcframe` untuk kompilasi sebagai berikut:
```
g++ -std=c++17 -D__TCFRAME_SPEC_FILE__="\"$SPEC_FILE\"" -I "$TCFRAME_HOME/include" -I "$TCFRAME_HOME/../tcrand/include" $TCFRAME_CXX_FLAGS -o "$RUNNER_EXEC" "$TCFRAME_HOME/src/tcframe/runner.cpp"
```

#### communicator

- Cara menjalankan communicator dan solution secara bersamaan (untuk mengetes solution)
```
mkfifo fifo
./communicator [input-file] < fifo | ./solution > fifo
```
- Perhatikan bahwa beberapa behavior dari communicator lokal dibandingkan dengan di server mungkin akan sedikit berbeda, terutama untuk solusi-solusi keliru.
